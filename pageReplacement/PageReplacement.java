package pageReplacement;


import java.util.*;






class PageAlgorithms
{
    public LinkedList<Integer> pages;
    public int total_pages;
    public int frames;
    public PageAlgorithms() 
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the total pages : " );
        this.total_pages = sc.nextInt();
        pages = new  LinkedList<Integer>();
        System.out.println("Enter the main memory frames : ");
        this.frames = sc.nextInt();
        System.out.println("Enter the sequence of pages : ");
        for(int i=0;i<total_pages;i++)
        {
            int a = sc.nextInt();
            pages.add(a);
        }


        sc.close();
    }   


    public void FCFS()
    {
        Queue<Integer>requested_pages = new LinkedList<>();

        int p_faults =0;
        int p_hits   =0;

        for(var i : pages)
        {
            if(requested_pages.contains(i))
            {
                p_hits++;
            }
            else{

                if(requested_pages.size()==frames)
                {
                    requested_pages.poll();

                }
                requested_pages.add(i);
                p_faults++;

            }
        }

        System.out.println("===== ===== ==== FCFS ==== ===== =====");
        System.out.println("PAGE HITS : "+p_hits);
        System.out.println("PAGE FAULTS : "+p_faults);

    }


    private void getOprimalFurther(ArrayList<Integer>rp,int curr,int nums)
    {
        int maxi = 0;
        int ind  = 0;
        int p    =0;
        for(var i : rp)
        {
            
            int j = curr;
            while(j<total_pages && pages.get(j)!=i)
            {
                j++;
            }

            if(maxi<j)
            {
                maxi =j;
                p=ind;
            }
            ind++;
        }

        rp.add(p,nums);
    }

    public void optimalReplace()
    {
        ArrayList<Integer>requseted_pages= new ArrayList<Integer>();
        int p_faults =0;
        int p_hits   =0;
        
        for(int i =0;i<total_pages;i++)
        {
            int page_req = pages.get(i);

            if(requseted_pages.contains(page_req))
            {
                p_hits++;
            }
            else{
                if(requseted_pages.size()==frames)
                {
                    this.getOprimalFurther(requseted_pages, i, page_req);;
                }
                else{
                    requseted_pages.add(page_req);

                }
                p_faults++;
            }
        }
        System.out.println("===== ===== ==== OPTIMAL PAGE REPLACEMNT ==== ===== =====");
        System.out.println("PAGE HITS : "+p_hits);
        System.out.println("PAGE FAULTS : "+p_faults);

    }

}


public class PageReplacement
{
    public static void main(String[] args) {
        System.out.println("Page replacement algorithms");

        PageAlgorithms pg = new PageAlgorithms();
        pg.FCFS();
        pg.optimalReplace();
    }
}