#define _CRT_SECURE_NO_WARNINGS // Visual Studio kullanıyorsanız bu satır gereklidir.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int dizi[],int len) {
	for (int i = 1; i < len; i++)
	{
		for (int j = 0; j < i; j++) {
			if (dizi[j]>dizi[i])//j daha büyük j yi kenara kaydırır i yani küçükler solda kalır 
			{
				int geç = dizi[j];
				dizi[j] = dizi[i];
				dizi[i] = geç;	
			}
		}
	}
}

void selection_sort(int dizi[], int len) {
	for (int i = 0; i < len; i++)
	{
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			if (dizi[j] < dizi[min])//küçük olanı bulur
			{
				min = j;
			}
		}
		int geç = dizi[i];//i den sonra gelen en küçük elemanı i ile değiştirir
		dizi[i] = dizi[min];
		dizi[min] = geç;
	}
}
void buble_sort(int dizi[], int len) {
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - 1; j++)
		{
			if (dizi[j] > dizi[j + 1])//j büyükse sola kayar küçükten sıralama yapar
			{
				int geç = dizi[j];
				dizi[j] = dizi[j + 1];
				dizi[j + 1] = geç;
			}
		}
	}
}


int main() {
	int dizi[10] = { 5, 2, 9, 1,  6, 7, 8, 3, 4 };
	buble_sort(dizi, 10);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", dizi[i]);
	}


	return 0;
}
