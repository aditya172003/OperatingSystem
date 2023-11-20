
package ProcessScheduling;

import java.util.*;
import java.util.Scanner;



class CompareProcess implements Comparator<Process>
{

    public CompareProcess()
    {
    }

    @Override
    public int compare(Process o1, Process o2)
    {
        
        if(o1.p_arrival_time==o2.p_arrival_time)
        {
            return 0;
        }
            return (o1.p_arrival_time>o2.p_arrival_time)?1:-1;
 
    }
    
}

class Compare implements Comparator<Process>
{

    public Compare()
    {
    }

    @Override
    public int compare(Process o1, Process o2)
    {
        if(o1.p_burst_time == o2.p_burst_time)
        {
            return (o1.p_arrival_time>o2.p_arrival_time)?1:-1;
        }
        return (o1.p_burst_time>o2.p_burst_time)?1:-1;
    }
    
}


class Process
{
    
        public int p_id;
        public int p_arrival_time;
        public int p_burst_time;
        public int p_complition_time;
        public int p_turn_around_time;
        public int p_waiting_time;
        public int p_priority;
   
        public Process()
        {
            p_complition_time   = 0;
            p_turn_around_time= 0;
            p_waiting_time        = 0;
            p_priority                 = 0;
                    
                    
        }
        public void getData()
        {   
                 Scanner sc = new Scanner (System.in);
                 
                 System.out.println("Enter Process_id : ");
                 this.p_id  = sc.nextInt();
                 
                 System.out.println("Enter arrival time : ");
                 this.p_arrival_time = sc.nextInt();
                 
                 System.out.println("Enter burst Time :");
                 this.p_burst_time   = sc.nextInt();
                 
                 System.out.println("Enter priority     : ");
                 this.p_priority = sc.nextInt();
                 
                 System.out.println("================================ ");
                        
        }
        
        
        public void setTime(int complition_time){
            this.p_complition_time = complition_time;
            this.p_turn_around_time = complition_time-p_arrival_time;
            
            this.p_waiting_time         = this.p_turn_around_time - this.p_burst_time;
        }
        
        public String toString()
        {
            return "(p"+this.p_id+")";
        }
        
        
}



class Scheduling_algorithms
{
    public ArrayList<Process>  process_list;
    public int total_processes;
    
    public Scheduling_algorithms()
    {
        
        process_list = new ArrayList<Process>();
        Scanner sc = new Scanner(System.in);
        
        System.out.println("Total  number of processes : ");
        this.total_processes = sc.nextInt();
        
        for(int i=0;i<total_processes;i++)
        {
            Process p  = new Process();
            p.getData();
            process_list.add(p);
        }
         
        Collections.sort(process_list,(o1,o2)->{
        if(o1.p_arrival_time==o2.p_arrival_time)
           {
               return 0;
           }
               return (o1.p_arrival_time>o2.p_arrival_time)?1:-1;

          });    
        
        System.out.println(process_list);
    }
    
    
    public void SJFPreemptive()
    {
       LinkedList<Process>waiting_list = new LinkedList<>(process_list);
       PriorityQueue<Process> readyQ = new PriorityQueue<Process>(new Compare());
       ArrayList<Process> completedSeq = new ArrayList<>();
       int average_waiting_time =0;
       int average_complition_time =0;
  
    
  
        Collections.sort(waiting_list, new Compare());
    
        int init_time =0;
     
        int processesDone=0;
        while(processesDone <total_processes)
        {
                   
            for(Process p : waiting_list)
            {
                if(p.p_arrival_time == init_time)
                {
                    readyQ.add(p);
                }
                
            }
            
            Process p  = readyQ.poll();
            
            if(p!=null)
            {
               
                p.p_burst_time--;
                if(p.p_burst_time == 0)
                {
                   p.setTime(init_time);
                   completedSeq.add(p);
                   processesDone++;
                   average_waiting_time +=p.p_waiting_time;
                   average_complition_time += p.p_complition_time;
                  
                }
                else
                {
                    readyQ.add(p);
                }
                System.out.print(" - |("+init_time+":"+p+")| -");
            }
            else
            {
                System.out.print(" - |(" +init_time+ ":"+" IDLE "+")| -");
            }
            
            init_time++;
            
        }
        
        System.out.println("|| done");
        System.out.println("Total complition time    : "+(init_time-1));
        System.out.println("Average waiting time       :  "+(average_waiting_time/total_processes));
        System.out.println("Average complition time  : "+ (average_complition_time/total_processes));
       
       
    }
    
    
    
}




public class Scheduling_Algorithm
{

    /** 
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        // TODO code application logic here
        Scheduling_algorithms s  = new Scheduling_algorithms();
        s.SJFPreemptive();
    }
    
}