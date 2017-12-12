import java.lang.Math;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static boolean is_prime(int x)
    {
        int h=(int)Math.sqrt(x);
        for(int i=2;i<=h;i++)
            if(x%i==0) return false;
        return true;
    }

    public static void main(String[] args) {
        int n;
        Scanner in=new Scanner(System.in);
        System.out.print("Input a number: ");
        n=in.nextInt();
        ArrayList<Integer> result=new ArrayList<>();
        for(int i=2;i<=n;i++) result.add(i);
        for(int i=2;i<=(int)Math.sqrt(n);i++)
        {
            if(is_prime(i))
            {
                final int t=i;
                result.removeIf(e->{return e%t==0&&t!=e;});
            }
        }
        System.out.println(result);
    }
}
