#ifndef SHOP_CART_H// 防止头文件被重复包含
#define SHOP_CART_H



// 声明购物车菜单函数
int shop_cart_menu();

// 声明购物车相关函数（在 shop_cart.c 中实现）
void show_inventory();
void add_to_cart();
void remove_from_cart();
void show_shopping_cart();
void handle_shop_cart();

#endif
