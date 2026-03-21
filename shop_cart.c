#include <stdio.h>
#include <string.h>
#include "shop_cart.h"
#include "inventory.h"

// 外部变量引用
extern struct inventory goods[NUM];
extern struct cart_item shopping_cart[NUM];
extern int cart_count;

/**
 * 显示商品库存信息
 */
void show_inventory() {
    FILE *fp;
    fp = fopen("inventory.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件！请先建立库存信息。\n");
        return;
    }
    
    int count = 0;
    // 打印表头
    printf("\n================================================================================\n");
    printf("%-12s %-8s %10s %10s %10s\n", "品名", "编号", "进价", "售价", "库存");
    printf("================================================================================\n");
    
    while (count < NUM && 
           fscanf(fp, "%s %s %f %f %d\n", 
                  goods[count].brand, 
                  goods[count].id, 
                  &goods[count].in_price, 
                  &goods[count].out_price, 
                  &goods[count].storage) == 5) {
        // 使用固定宽度格式化输出，确保对齐
        printf("%-12s %-8s %8.2f %8.2f %8d\n", 
               goods[count].brand,      // 左对齐，宽度 12
               goods[count].id,         // 左对齐，宽度 8
               goods[count].in_price,   // 右对齐，宽度 8，保留 2 位小数
               goods[count].out_price,  // 右对齐，宽度 8，保留 2 位小数
               goods[count].storage);   // 右对齐，宽度 8
        count++;
    }
    printf("================================================================================\n");
    fclose(fp);
}

/**
 * 添加商品到购物车
 */
void add_to_cart() {
    char input_id[20];
    int quantity;
    int found = 0;
    
    // 先显示库存商品信息
    show_inventory();
    
    printf("\n请输入要添加到购物车的商品编号：");
    scanf("%s", input_id);
    
    // 查找商品
    for (int i = 0; i < NUM; i++) {
        if (strcmp(goods[i].id, input_id) == 0) {
            found = 1;
            
            // 检查库存是否充足
            printf("当前库存：%d\n", goods[i].storage);
            printf("请输入购买数量：");
            scanf("%d", &quantity);
            
            if (quantity <= 0) {
                printf("购买数量必须大于 0！\n");
                return;
            }
            
            if (quantity > goods[i].storage) {
                printf("库存不足！最多可购买 %d 件。\n", goods[i].storage);
                return;
            }
            
            // 检查购物车中是否已有该商品
            int exist = 0;
            for (int j = 0; j < cart_count; j++) {
                if (strcmp(shopping_cart[j].product.id, input_id) == 0) {
                    // 更新数量
                    shopping_cart[j].quantity += quantity;
                    exist = 1;
                    printf("购物车中该商品数量已更新！\n");
                    break;
                }
            }
            
            if (!exist) {
                // 添加到购物车
                if (cart_count >= NUM) {
                    printf("购物车已满，无法添加更多商品！\n");
                    return;
                }
                shopping_cart[cart_count].product = goods[i];
                shopping_cart[cart_count].quantity = quantity;
                cart_count++;
                printf("商品已成功添加到购物车！\n");
            }
            break;
        }
    }
    
    if (!found) {
        printf("未找到编号为 %s 的商品！\n", input_id);
    }
}

/**
 * 从购物车删除商品
 */
void remove_from_cart() {
    char input_id[20];
    int found = -1;
    
    // 先显示购物车内容
    if (cart_count == 0) {
        printf("购物车为空！\n");
        return;
    }
    
    show_shopping_cart();
    
    printf("\n请输入要删除的商品编号：");
    scanf("%s", input_id);
    
    // 查找商品在购物车中的位置
    for (int i = 0; i < cart_count; i++) {
        if (strcmp(shopping_cart[i].product.id, input_id) == 0) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("购物车中没有编号为 %s 的商品！\n", input_id);
        return;
    }
    
    // 删除商品（将后面的商品前移）
    for (int i = found; i < cart_count - 1; i++) {
        shopping_cart[i] = shopping_cart[i + 1];
    }
    cart_count--;
    
    printf("商品已从购物车删除！\n");
}

/**
 * 显示购物车内容
 */
void show_shopping_cart() {
    if (cart_count == 0) {
        printf("购物车为空！\n");
        return;
    }
    
    float total = 0.0;
    
    printf("\n************************************\n");
    printf("\t\t购物车清单\n");
    printf("************************************\n");
    printf("================================================================================\n");
    printf("%-12s %-8s %10s %10s %10s\n", "品名", "编号", "单价", "数量", "小计");
    printf("================================================================================\n");
    
    for (int i = 0; i < cart_count; i++) {
        float subtotal = shopping_cart[i].product.out_price * shopping_cart[i].quantity;
        total += subtotal;
        
        printf("%-12s %-8s %10.2f %10d %10.2f\n", 
               shopping_cart[i].product.brand,
               shopping_cart[i].product.id,
               shopping_cart[i].product.out_price,
               shopping_cart[i].quantity,
               subtotal);
    }
    
    printf("================================================================================\n");
    printf("总计：%.2f 元\n", total);
    printf("************************************\n");
}

/**
 * 购物车菜单处理函数
 */
void handle_shop_cart() {
    int select;
    
    while (1) {
        select = shop_cart_menu();
        
        switch (select) {
            case 1:
                show_inventory();
                break;
            case 2:
                add_to_cart();
                break;
            case 3:
                remove_from_cart();
                break;
            case 4:
                printf("退出购物车菜单。\n");
                return;
            default:
                printf("输入错误，请重新选择！\n");
        }
        
        printf("\n按任意键继续...");
        getchar();  // 消耗换行符
        getchar();  // 等待用户按键
    }
}
