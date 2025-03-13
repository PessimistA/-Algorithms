package algorithms;

class bubble_sorting{
	private int[] dizi;
	public bubble_sorting(int[] dizi) {
		this.dizi= dizi;
		sort();
	}
	private void sort() {
		for (int i = 0; i < dizi.length-1; i++) {
			for (int j = 0; j < dizi.length-i-1; j++) {
				if (dizi[j]>dizi[j+1]) {
					swap(j, j+1);
				}
			}
		}
	}
	private void swap(int i,int j) {
		int temp = dizi[i];
		dizi[i]= dizi[j];
		dizi[j] = temp;
	}
	public void print() {
		for (int i = 0; i < dizi.length; i++) {
			System.out.printf("%d ",dizi[i]);
		}
	}
	
}

public class bubble_sort {
	public static void main(String[] args) {
		int[] dizi= {1,3,12,5,8,9};
		bubble_sorting bSorting= new bubble_sorting(dizi);
		bSorting.print();
	}
}
