import java.util.*;

public class FindKCloest {

    private FindKCloest() { }

    public static List<Integer> findClosestElements(int[] arr, int k, int x) {
        
        List<Integer> arrList = new ArrayList<Integer>();
        
        // Add array values to ArrayList
        for (int i=0; i < arr.length; i++)
            arrList.add(arr[i]);
        
        // Sort with compare funciont defined with lambda expression
        Collections.sort(arrList, (a, b) -> Math.abs(a - x) - Math.abs(b - x));
       
        // The k closest elements
        arrList = arrList.subList(0, k);
       
        // Sort to return elments in order
        Collections.sort(arrList);
        return arrList;
    }

    public static void main(String[] args){
        int[] arr = {1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5};
        int x = 3;
        int k = 2;

        List<Integer> result = new ArrayList<Integer>(findClosestElements(arr, k, x));

        System.out.println(result);
    }
}