package algorithms;

import java.util.Scanner;

class hash{
	private int[] table;
	private int size;
    private static final int EMPTY = -1;  // Boş hücreleri belirtmek için
    private static final int DELETED = -2; 
	public hash(int size){
		this.table=new int[size];
		this.size=size;
		
		for (int i = 0; i < size; i++) {
			table[i]=EMPTY;
		}
	}
	private int hashFunction(int key,int i) {
		return (key%size+i)% size;
	}
	
	public void insert(int key) {
		int i=0;
		while (i!=size) {
			int j = hashFunction(key, i);
			if (table[j]==EMPTY) {
				table[j]=key;
				return;
			}
			else {
				i+=1;
			}
		}
	}
	private int search(int key) {
		int i=0;
		while (i!=size) {
			int j = hashFunction(key, i);
			if (table[j]==key) {
				return j;
			}
			else {
				i+=1;
			}
		}
		return EMPTY;
	}
	public void take() {
		System.out.println("aradığınız key değerini giriniz");
		Scanner scnScanner = new Scanner(System.in);
		int key = scnScanner.nextInt();
		int index = search(key);
		System.out.println(key+" değerinin bulunduğu index\""+index+"'dir\"");
	}
	public void print() {
		for (int i = 0; i < size; i++) {
			System.out.printf("[%d]->%d\n",i,table[i]);
			
		}
	}
	public void delete(int key) {
		int index = search(key);
	    if (index != -1) { 
	        table[index] = DELETED; 
	    }
	}
	
}



public class hash_açık_adresleme {
	public static void main(String[] args) {
		hash hsHash= new hash(10);
		hsHash.insert(15);
		hsHash.take();
		hsHash.print();
		hsHash.delete(15);
		hsHash.print();
	}
}
