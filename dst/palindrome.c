#include <stdio.h>
int main() {
	int n; 
	scanf("%d", &n);
       int original = n;
       int reversed = 0;
       int tmp = n;
       while(tmp >  0){
           reversed = reversed*10 + tmp%10;
	   tmp = tmp/10;

       }
	if (original == reversed) {
		printf("Y\n");
	} else {
		printf("N\n");
	}
	return 0;
}
