#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checkout.h"
#include "shop_cart.h"
#include "inventory.h"

// 外部变量引用
extern struct inventory goods[NUM];
extern struct cart_item shopping_cart[NUM];
extern int cart_count;

/**
 * 结算功能：完成支付，更新库存，打印小票
 */
void checkout() {
    if (cart_count == 0) {
        printf("购物车为空，无法结算！\n");
        return;
    }
    
    // 显示购物车清单
    show_shopping_cart();
    
    // 计算总金额
    float total = 0.0;
    for (int i = 0; i < cart_count; i++) {
        total += shopping_cart[i].product.out_price * shopping_cart[i].quantity;
    }
    
    printf("\n应付总额：%.2f 元\n", total);
    
    // 处理支付
    float payment;
    printf("请输入支付金额：");
    scanf("%f", &payment);
    
    if (payment < total) {
        printf("支付金额不足，结算取消！\n");
        return;
    }
    
    float change = payment - total;
    if (change > 0) {
        printf("找零：%.2f 元\n", change);
    }
    
    // 更新库存
    FILE *fp;
    fp = fopen("inventory.txt", "w");
    if (fp == NULL) {
        printf("无法打开库存文件，库存更新失败！\n");
        return;
    }
    
    // 遍历所有商品，更新库存后写入文件
    for (int i = 0; i < NUM; i++) {
        // 检查该商品是否在购物车中
        for (int j = 0; j < cart_count; j++) {
            if (strcmp(goods[i].id, shopping_cart[j].product.id) == 0) {
                // 从库存中减去购买数量
                goods[i].storage -= shopping_cart[j].quantity;
                break;
            }
        }
        
        // 将更新后的商品信息写入文件
        fprintf(fp, "%s %s %f %f %d\n", 
                goods[i].brand, 
                goods[i].id, 
                goods[i].in_price, 
                goods[i].out_price, 
                goods[i].storage);
    }
    
    fclose(fp);
    
    // 打印购物小票
    printf("\n");
    printf("========================================\n");
    printf("\t\t购物小票\n");
    printf("========================================\n");
    printf("品名\t\t编号\t单价\t数量\t小计\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < cart_count; i++) {
        float subtotal = shopping_cart[i].product.out_price * shopping_cart[i].quantity;
        printf("%-12s %-8s %.2f\t%d\t%.2f\n", 
               shopping_cart[i].product.brand,
               shopping_cart[i].product.id,
               shopping_cart[i].product.out_price,
               shopping_cart[i].quantity,
               subtotal);
    }
    
    printf("----------------------------------------\n");
    printf("总计：%.2f 元\n", total);
    printf("实收：%.2f 元\n", payment);
    if (change > 0) {
        printf("找零：%.2f 元\n", change);
    }
    printf("========================================\n");
    printf("感谢惠顾，欢迎下次光临！\n");
    printf("========================================\n");
    
    // 清空购物车
    cart_count = 0;
    
    printf("\n结算完成，库存已更新！\n");
}
