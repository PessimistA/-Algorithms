package algorithms;

class insertion_sorting{
	private int[] dizi;
	public insertion_sorting(int[] dizi) {
		this.dizi= dizi;
		sort();
	}
	private void sort() {
		for (int i = 1; i < dizi.length; i++) {
			int key = dizi[i];
			int j=i-1;
			while (j>0 &&dizi[j]>key) {
				dizi[j+1] = dizi[j];
				j = j-1;
			}
			dizi[j+1] = key;
			
		}
	}
	public void print() {
		for (int i = 0; i < dizi.length; i++) {
			System.out.printf("%d ",dizi[i]);
		}
	}
}

public class insertion_sort {
	public static void main(String[] args) {
		int[] dizi= {1,3,12,5,8,9};
		insertion_sorting select1= new insertion_sorting(dizi);
		select1.print();	
	}
}

//bu sort algoritması dizideki en küçük elemanı bulur ve başa koyar

/*
worst case performance :	O(n2) comparisons,
							O(n2) swaps
							
best case performance:		O(n) comparisons,
							O(1) swaps
							
average performance:		O(n2) comparisons,
							O(n2) swaps
							
Worst-case space complexity:  O(n) total,O(1) auxililary

animation:en.wikipedia.org


*/
