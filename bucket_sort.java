package algorithms;

import java.util.ArrayList;
import java.util.Collections;

class BucketSort {
    void bucketSort(float arr[]) {
        int n = arr.length;
        ArrayList<Float>[] buckets = new ArrayList[n];

        for (int i = 0; i < n; i++) {
            buckets[i] = new ArrayList<>();
        }

        for (float num : arr) {
            int index = (int) (num * n);
            buckets[index].add(num);
        }

        for (int i = 0; i < n; i++) {
            Collections.sort(buckets[i]);
        }

        int index = 0;
        for (ArrayList<Float> bucket : buckets) {
            for (float num : bucket) {
                arr[index++] = num;
            }
        }
    }
}

public class bucket_sort {
    public static void main(String args[]) {
        float arr[] = {0.897f, 0.565f, 0.656f, 0.123f, 0.665f, 0.343f};
        BucketSort ob = new BucketSort();
        ob.bucketSort(arr);
        System.out.println("Bucket Sort Sonucu: ");
        for (float num : arr) {
            System.out.print(num + " ");
        }
    }
}
