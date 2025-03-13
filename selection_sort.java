package algorithms;

import java.util.Iterator;

class Selection_with_mim{
	private int[] dizi;
	public Selection_with_mim(int[] dizi) {
		this.dizi= dizi;
		sort();
	}
	private void sort() {
		for (int i = 0; i < dizi.length-1; i++) {
			int min=mim(i);
			swap(min, i);
		}
	}

	private int mim(int k) {
		int min=k;
		for (int i = k+1; i < dizi.length; i++) {
			if (dizi[min]> dizi[i]) {
				min = i;
			}
		}
		return min;
	}
	private void swap(int mim,int index) {
		int temp = dizi[index];
		dizi[index]= dizi[mim];
		dizi[mim] = temp;
	}
	public void print() {
		for (int i = 0; i < dizi.length; i++) {
			System.out.printf("%d ",dizi[i]);
		}
	}
}

class Selection_without_mim{
	private int[] dizi;
	public Selection_without_mim(int[] dizi) {
		this.dizi= dizi;
		sort();
	}
	private void sort() {
		for (int i = 0; i < dizi.length-1; i++) {
			int min=i;
			for (int j = i+1; j < dizi.length; j++) {
				if (dizi[min]> dizi[j]) {
					min =j;
				}
			}
			swap(min, i);
		}
	}

	private void swap(int mim,int index) {
		int temp = dizi[index];
		dizi[index]= dizi[mim];
		dizi[mim] = temp;
	}
	public void print() {
		for (int i = 0; i < dizi.length; i++) {
			System.out.printf("%d ",dizi[i]);
		}
	}
}

public class selection_sort {
	public static void main(String[] args) {
		int[] dizi= {1,3,12,5,8,9};
		Selection_with_mim select= new Selection_with_mim(dizi);
		select.print();
	}
}



//bu sort algoritması dizideki en küçük elemanı bulur ve başa koyar

/*
worst case performance :	O(n2) comparisons,
							O(n) swaps
							
best case performance:		O(n2) comparisons,
							O(1) swaps
							
average performance:		O(n2) comparisons,
							O(n) swaps
							
Worst-case space complexity:  O(1) auxililary

animation:en.wikipedia.org


*/