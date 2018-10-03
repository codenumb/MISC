#include<stdio.h>
/**
  *Question:
  *given non negative interger representing the histogram's bar height where the width of each bar is 1 find
  *the area of largest rectangle in the histogram
  */
int main()
{
	int i,j,max=0,amin;int a[6]={0};
	printf("enter histogram array\n");
	for(i=0;i<6;i++)
		scanf("%d",&a[i]);
	for(i=0;i<6;i++)
	{
		if(a[i]!=0){
		//printf("a[%d]=%d\n",i,a[i]);
		max=max>a[i]?max:a[i];
		amin=a[i];
		for(j=1;j<6-i;j++)
		{
			if(a[i+j]==0)break;
			if(a[i+j]>=amin){
				//printf("a[%d+%d]=%d\n",i,j,a[i+j]);
				max=max>(a[i+j]>amin*(j+1)?a[i+j]:amin*(j+1))?max:(a[i+j]>amin*(j+1)?a[i+j]:amin*(j+1));
				//printf("maxa=%d\n",max);
			}
			else
			{
				amin=a[i+j];
				max=max>(max>amin*(j+1)?max:amin*(j+1))?max:(max>amin*(j+1)?max:amin*(j+1));
			}		
		}
			//printf("max=%d\n",max);
	}}
	printf("max=%d\n",max);
	return 0;
}
