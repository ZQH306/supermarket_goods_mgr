#ifndef INVENTORY_H // 防止头文件被重复包含
#define INVENTORY_H

// 商品结构体定义
#define NUM 5

struct inventory
{
    char brand[20]; //商品名称
    char id[20];    //商品编号
    float in_price; //进价
    float out_price;//售价
    int storage;    //库存
};

// 购物车商品结构体
struct cart_item
{
    struct inventory product; //商品信息
    int quantity;             //购买数量
};

// 全局变量声明
extern struct inventory goods[NUM];   //商品数组
extern struct cart_item shopping_cart[NUM]; //购物车数组
extern int cart_count;  //购物车中商品品种数

// 声明 inventory 函数
int inventory();



#endif
