#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <QVector3D>
#include <QDebug>
#include <fstream>
#include <sstream>
#include <cstring>
#include <QtMath>

struct Point{
    QVector3D position;
    QVector3D color;
};

class PointClould{
public:
    PointClould(){}
    std::vector<Point> points;

    bool loadPLY(const QString& path)
    {
        std::ifstream file(path.toStdString());
        if(!file.is_open()){
            qDebug()<<"open PLY file faild\n";
            return false;
        }

        std::string line;
        int vertexCount = 0;
        bool header = true;

        while(std::getline(file, line)){
            if(header){
                if(line.find("element vertex") != std::string::npos){
                    sscanf(line.c_str(), "element vertex %d", &vertexCount);
                }
                if(line == "end_header"){
                    header = false;
                }
            }else{
                float x,y,z;
                int r = 255,g =0.0, b = 0.0;
                std::stringstream ss(line);
                if(!(ss >> x >> y >> z))
                    continue;
                if(x > 1.0)
                    continue;

                Point p;
                p.position = QVector3D(x,y,x);
                p.color = QVector3D(r/255.0f, g/255.0f, b/255.0f);

                points.push_back(p);
            }
        }
        return true;
    }


    float readFloatBigEndian(std::ifstream& file)
    {
        char bytes[4];
        file.read(bytes, 4);

        // 字节翻转（大端 → 小端）
        std::swap(bytes[0], bytes[3]);
        std::swap(bytes[1], bytes[2]);

        float value;
        std::memcpy(&value, bytes, 4);
        return value;
    }

    bool loadPLYBinaryBigEndian(const QString& path)
    {
        std::ifstream file(path.toStdString(), std::ios::binary);
        if (!file.is_open()) {
            qDebug() << "open PLY file failed";
            return false;
        }

        std::string line;
        int vertexCount = 0;
        bool isBinary = false;

        // ========= 解析 header =========
        while (std::getline(file, line)) {
            if (line.find("format binary_big_endian") != std::string::npos) {
                isBinary = true;
            }

            if (line.find("element vertex") != std::string::npos) {
                sscanf(line.c_str(), "element vertex %d", &vertexCount);
            }

            if (line == "end_header") {
                break;
            }
        }

        if (!isBinary) {
            qDebug() << "Not binary big endian format!";
            return false;
        }

        qDebug() << "vertexCount =" << vertexCount;

        // ========= 读取点数据 =========
        points.clear();
        points.reserve(vertexCount);

        for (int i = 0; i < vertexCount; i++) {
            float x = readFloatBigEndian(file);
            float y = readFloatBigEndian(file);
            float z = readFloatBigEndian(file);

            Point p;
            p.position = QVector3D(x, y, z);

            // 默认白色
            p.color = QVector3D(1.0f, 1.0f, 1.0f);

            points.push_back(p);
        }

        return true;
    }
};


struct AABB{
    QVector3D center;
    float halfSize;

    bool contains(const QVector3D &p) const{
        return qFabs(p.x() - center.x()) <= halfSize &&
               qFabs(p.y() - center.y()) <= halfSize &&
               qFabs(p.z() - center.z()) <= halfSize;
    }

    bool intersects(const AABB& other) const{
        return (qFabs(center.x() - other.center.x()) <= halfSize + other.halfSize ||
                qFabs(center.y() - other.center.y()) <= halfSize + other.halfSize ||
               qFabs(center.z() - other.center.z()) <= halfSize + other.halfSize);
    }

    static AABB computeBoundingBox(const std::vector<Point> &pts)
    {
        float value = 1000.0f;
        QVector3D minP(value, value, value);
        QVector3D maxP(-value, -value, -value);

        for(auto &p : pts)
        {
            minP.setX(std::min(minP.x(), p.position.x()));
            minP.setY(std::min(minP.y(), p.position.y()));
            minP.setZ(std::min(minP.z(), p.position.z()));

            maxP.setX(std::max(maxP.x(), p.position.x()));
            maxP.setY(std::max(maxP.y(), p.position.y()));
            maxP.setZ(std::max(maxP.z(), p.position.z()));
        }
        QVector3D center = (minP + maxP) / 2.0;
        float halfSize = std::max({maxP.x() - minP.x(), maxP.y() - minP.y(), maxP.z() - minP.z()}) / 2.0f;
        return {center, halfSize};
    }
};

class OcTreeNode{
public:
    AABB boundary;
    int capacity;
    int depth;
    int maxDepth;

    std::vector<Point> points;
    std::unique_ptr<OcTreeNode> children[8];

    bool divided = false;

    OcTreeNode(AABB box, int cap, int d, int maxD)
        :boundary(box),capacity(cap),depth(d),maxDepth(maxD)
    {

    }

    bool insert(const Point& p){
        if(!boundary.contains(p.position)){
            return false;
        }

        if(points.size() < capacity || depth >= maxDepth){
            points.push_back(p);
            return true;
        }

        if(!divided) subdivide();

        for(int i = 0; i < 8; i++){
            if(children[i]->insert(p))
                return true;
        }
        return false;
    }

    void subdivide(){
        float h = boundary.halfSize / 2.0f;

        for(int i = 0; i < 8; i++){
            QVector3D offset(
                (i & 1) ? h : -h,
                (i & 2) ? h : -h,
                (i & 4) ? h : -h
            );

            children[i] = std::make_unique<OcTreeNode>(
                AABB{boundary.center + offset, h},
                capacity,
                depth + 1,
                maxDepth
            );
        }

        divided = true;

        //重新分配已有点
        for(auto &p : points){
            for(int i = 0; i< 8; i++)
                if(children[i]->insert(p))
                    break;
        }
        points.clear();
    }

    void queryLOD(const QVector3D &cameraPos, float threshold, std::vector<Point> &result){
        float dist = (boundary.center - cameraPos).length();

        //LOD策略：远距离直接用当前节点代表点
        if(dist > threshold || !divided){
            if(!points.empty())
                result.push_back(points[0]);//简化取代表点
            return;
        }

        for(int i = 0; i < 8; i++)
        {
            if(children[i])
                children[i]->queryLOD(cameraPos,threshold, result);
        }
    }

    void query(const AABB& range, std::vector<Point>& found){
        if(!boundary.intersects(range))
            return;

        for(auto&p : points)
            if(range.contains(p.position))
                found.push_back(p);

        if(divided)
            for(int i = 0; i < 8; i++)
                children[i]->query(range, found);
    }

    void clear()
    {
        points.clear();

        if(divided){
            for(int i = 0; i < 8; i++)
                if(children[i]){
                    children[i]->clear();
                    children[i].reset();
                }
        }
        divided = false;
    }
};

class Octree{
private:
    std::unique_ptr<OcTreeNode> root;
public:
    Octree(const AABB& boundary, int capacity, int maxDepth){
        root = std::make_unique<OcTreeNode>(boundary, capacity, 0, maxDepth);
    }
    void insert(const Point& point){
        root->insert(point);
    }
    std::vector<Point> query(const AABB& range){
        std::vector<Point> result;
        root->query(range, result);
        return result;
    }

    void queryLOD(const QVector3D &cameraPos, float threshold, std::vector<Point> &result)
    {
        root->queryLOD(cameraPos,threshold, result);
    }

    void clear()
    {
        root->clear();
    }
};
#endif // POINTCLOUD_H
