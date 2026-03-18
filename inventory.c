#include <stdio.h>
#include "menu.h"
#include "inventory.h"

#define NUM 5

struct inventory
{
    char brand[20]; //商品名称
    char id[20];    //商品编号
    float in_price; //进价
    float out_price;//售价
    int storage;    //库存
};

struct inventory goods[NUM];   //商品结构体数组，该数组可以存储NUM个商品结构体

int inventory()
{ 
switch (menu()){
		case 1: printf("1.建立库存信息\n");
        {
            FILE *fp; //文件指针
            fp = fopen("inventory.txt", "w");//打开文件
            if (fp == NULL){
                printf("无法打开文件！\n");
                return 0;
            }
            
            for (int i = 0; i < NUM; i++) //循环输入NUM个商品信息
            {
                printf("请输入第%d个商品信息:\n", i + 1);
                printf("请输入商品名称：");
                scanf("%s", goods[i].brand);
                printf("请输入商品编号：");
                scanf("%s", goods[i].id);
                printf("请输入商品进价：");
                scanf("%f", &goods[i].in_price);
                printf("请输入商品售价：");
                scanf("%f", &goods[i].out_price);
                printf("请输入商品库存：");
                scanf("%d", &goods[i].storage);
        
                fprintf(fp, "%s %s %f %f %d\n", goods[i].brand, goods[i].id, goods[i].in_price, goods[i].out_price, goods[i].storage);//写入文件
               
            }
                fclose(fp);//关闭文件
                printf("商品信息已保存！\n");//提示保存成功
                return 0;
            
        }break;

		case 2: printf("2.显示库存信息\n");
        {
            FILE *fp; //指向文件的指针
            fp = fopen("inventory.txt", "r");
            if (fp == NULL) {
                printf("无法打开文件！\n");
                return 0;
            }
            
            int count = 0;
            // 打印表头
            printf("================================================================================\n");
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
        }break;
	}
}


