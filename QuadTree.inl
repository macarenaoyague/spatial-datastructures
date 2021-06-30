#include "QuadTree.h"
#include <memory>
#include <iostream>
#include <vector>

namespace utec
{
namespace spatial
{

template<typename Node, typename Rectangle, typename Point>
QuadTree<Node, Rectangle, Point>::QuadTree(){
    this->root=nullptr;
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::insert(Point new_point){
    std::shared_ptr<Node>& target = search(new_point, this->root);
    if(target==nullptr){
        target=std::make_shared<Node>(new_point);
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node>& QuadTree<Node, Rectangle, Point>::search(Point target, std::shared_ptr<Node>& node){
    if(node == nullptr){
        return node; //not found
    } else if(node->get_point() == target){
        return node;
    }
    
    auto cur_point = node->get_point();

    const int x=0, y=1;

    if(target.get(x) < cur_point.get(x)){
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NW());
        else
            return search(target, node->SW());
    }else{
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NE());
        else
            return search(target, node->SE());
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node> QuadTree<Node, Rectangle, Point>::search(Point target){
    return search(target, this->root);
}

template<typename Node, typename Rectangle, typename Point>
bool QuadTree<Node, Rectangle, Point>::match(Rectangle region, std::shared_ptr<Node>& node) {

    // esto es si hay match
    // hacer dibujo si es que no
    const int x = 0, y = 1;
    auto cur_point = node->get_point();
    auto region_min = region._min;
    auto region_max = region._max;

    bool min_limit = region_min.get(x) <= cur_point.get(x) && region_min.get(y) <= cur_point.get(y);
    bool max_limit = region_max.get(x) >= cur_point.get(x) && region_max.get(y) >= cur_point.get(y);

    if(min_limit && max_limit) return true;
    return false;
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::range(Rectangle region, std::shared_ptr<Node>& node, std::vector<Point>& points){
    if(node != nullptr) {

        if (match(region, node)) 
            points.push_back(node->get_point());

        range(region, node->NW(), points);
        range(region, node->SW(), points);
        range(region, node->NE(), points);
        range(region, node->SE(), points);

    }

    // el punto divide la región en 4    

    // lo que está a su derecha arriba
    // lo que está a su derecha abajo
    // lo que está a su izquierda arriba
    // lo que está a su izquierda abajo
}



template<typename Node, typename Rectangle, typename Point>
std::vector<Point> QuadTree<Node, Rectangle, Point>::range(Rectangle region){
    std::vector<Point> points;
    range(region, this->root, points);
    return points;
}

template<typename Node, typename Rectangle, typename Point>
Point QuadTree<Node, Rectangle, Point>::nearest_neighbor(Point reference){
    // TODO
}

} //spatial
} //utec
