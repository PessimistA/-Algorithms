// İki tam sayının basamak sayısını bulur
int getSize(int num) {
    int size = 0;
    while (num) {
        num /= 10;
        size++;
    }
    return size;
}

// Karatsuba algoritmasını uygular
long long karatsuba(int x, int y) {
    if (x < 10 || y < 10) {
        return x * y;
    }
    
    int size = fmax(getSize(x), getSize(y));
    int m = size / 2;
    int power = pow(10, m);
    
    int x_high = x / power;
    int x_low = x % power;
    int y_high = y / power;
    int y_low = y % power;
    
    long long z0 = karatsuba(x_low, y_low);
    long long z1 = karatsuba((x_low + x_high), (y_low + y_high));
    long long z2 = karatsuba(x_high, y_high);
    
    return (z2 * pow(10, 2 * m)) + ((z1 - z2 - z0) * pow(10, m)) + z0;
}

int main() {
    int num1 = 1234;
    int num2 = 5678;
    
    printf("%d * %d = %lld\n", num1, num2, karatsuba(num1, num2));
    return 0;
}

// T(n) = 3T(n/2) +Q(n) -> Q(n) sebebi     int x_high = x / power; gibi işlemler n kez döner
