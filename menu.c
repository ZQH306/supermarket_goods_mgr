#include <stdio.h>


// 开始菜单
int menu(){
	int select;

	printf("************************************\n");
	printf("\t欢迎进入超市管理系统\n");
	printf("************************************\n");

	printf("请选择数字进行操作：\n");
	printf("1.建立库存信息\n");
	printf("2.显示库存信息\n");
	printf("3.购物车\n");
	printf("4.结算\n");
	printf("5.退出\n");

	printf("请选择对应数字1--5:\n");

	while (1){

		scanf("%d",&select);  // 从键盘获取一个数据存入变量

		if(select < 1 || select > 5){
			printf("输入错误，请重新输入：\n");
		}
		else{
			break;
		}
		return select;
	}
}
