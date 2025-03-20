package algorithms;

class Heap1{
	private int n;
	private int[] array;
	public Heap1(int array[]) {
		// TODO Auto-generated constructor stub
		this.array=array;
		n=array.length;
	}
	public void max_heapify(int i) {
		int parent= i;
		int leftC= (2*i)+2;
		int rightC= (2*i)+1;
		if (leftC < n && array[leftC] > array[parent]) {//eğer parentten büyükse değiştir
			parent= leftC;
		}
        if (rightC < n && array[rightC] > array[parent]) {//sağ çocuk büyükse onu büyük yap
            parent = rightC;
        }
        // Eğer en büyük değişmişse, düğümleri swap yap ve devam et
        if (parent != i) {
            int temp = array[i];
            array[i] = array[parent];
            array[parent] = temp;

            max_heapify(parent);
        }
	}
	
	public void build_heap() {
	   
		for (int i = n / 2 - 1; i >= 0; i--){ 
	    	max_heapify(i);
	    }

	}
	
	public void heap_sort() {
		build_heap();
		for (int i=n-1; i>0 ; i--) {
			int temp = array[0];
			array[0] = array[i];
			array[i] = temp;
			n--;
			max_heapify(0);
			
		}
	}
	public void print() {
	      for (int num : array) {
	            System.out.print(num + " ");
	        }
	        System.out.println();
	}
	
}


public class heap {
	public static void main(String[] args) {
		int[] array = {4,1,3,2,16,9,10,14,8,7};
		Heap1  heap1 = new Heap1(array);
		heap1.heap_sort();
		heap1.print();
	}
}
