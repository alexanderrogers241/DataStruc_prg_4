/*
Student Name: Alexander Rogers
Student NetID: abr241
Compiler Used: Visual Studio
Program Description: Program assignment 4
Assigned Oct 2020
*/

#include <sstream> 
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include "Node.h"

bool cmp_starttime(std::shared_ptr<Node> b, std::shared_ptr<Node> a)
{
    if (a->priority > b->priority)
        return true;
    else if (a->priority < b->priority)
        return false;
    else if (a->priority == b->priority)
    {
        // then compare arrival time or start time
        if (a->start_time < b->start_time)
            return true;
        else if (a->start_time > b->start_time)
            return false;
        else if (a->start_time == b->start_time)
        {
            // then compare elapsed time
            if (a->elapsed_time > b->elapsed_time)
                return true;
            else if (a->elapsed_time < b->elapsed_time)
                return false;
            else if (a->start_time == b->start_time)
            {



                return true;


            }





        }





    }





    // return true if a comes before b
//return a->start_time < b->start_time;
}


bool exit_fun(std::vector<std::string>& cmd_input)
{
    // exit function
    std::cout << "Exiting porgram\n";
    return true;

}
bool load_file(std::vector<std::string>& cmd_input, std::vector<std::string>& cmd_output)
{
    // modified code from example at https://www.learncpp.com/cpp-tutorial/186-basic-file-io/

    std::ifstream inf{ cmd_input[0] }; //should contain the name of the file along with its . suffix
    std::stringstream ss; // repeat main
// error handling

    if (!inf)
    {
        std::cout << "\n";
        std::cout << "Error: file could not be accessed.\n";
        return false;
    }

    // parse files contents
    while (inf)
    {
        std::string strInput;
        std::getline(inf, strInput); //puts line in strInput
        if (!(strInput == ""))
        {
            cmd_output.push_back(strInput);
        }
    }

    return true;
}
void output_BST(std::string ss, std::string name)
{
    // modified code from example at https://www.learncpp.com/cpp-tutorial/186-basic-file-io/

    std::ofstream outf{ name, std::ios::app };

    if (!outf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, Sample.dat could not be opened for writing!" << std::endl;
        return;
    }
    outf << ss << "\n";
    // write BST into file.



}
int main()
{
    bool load_in_prog = false;
    bool finished_load = true;
    bool exit_program = false;
    std::cin; // declaring for getline
    std::string str_input;
    std::string cmd;
    std::vector<std::string> cmd_input;
    std::vector<std::string> cmd_output; // used for data output from loaded ext files
    std::vector<std::shared_ptr<Node>> list;
    std::vector<std::shared_ptr<Node>> heap;
    std::shared_ptr<Node> active_task = nullptr;
    bool simulate = false;
    // SIMULATION VARIABLES
    int sim_time = 0;


    do
    {

        cmd_input.clear();// resets program

        // modified code from example at https://www.learncpp.com/cpp-tutorial/56-do-while-statements/
        do
        {
            std::cout << "\nWelcome to Program 4: SCHEDULE \n";
            std::cout << "Please use the following commands: \n \n";
            std::cout << "1) exit - exits the program\n";
            std::cout << "2) load <file> - parses .txt file\n";
            std::cout << "3) register <task> <priority> <length> <arrives> - registers/add the task with the given priority ect\n";
            std::cout << "4) remove <task> - removes the specified task from the scheduled vector\n";
            std::cout << "5) clear - empties the schedule\n";
            std::cout << "6) display - in scheduling, displays task. In simulation mode, displays active task, list of tasks to be scheduled, and current time step.\n";
            std::cout << "7) simulate - simulation mode\n";
            std::cout << "8) schedule - schedule mode\n";
            std::cout << "9) step - moves simulation forward one step\n";
            std::cout << "10) run - run the simulation until the last task has completed\n";
            std::cout << "11) run till <time> - run the simulation until the specified time unit has been reached.\n";
            std::cout << "12) reset - resets the time to 0 and empties the priority queue\n";
            std::cout << "****REGISTER,REMOVE,CLEAR only schedule mode\n\n";
            std::cout << "****STEP,RESET,RUN only simluation mode\n\n";

            std::getline(std::cin, str_input);
        } while (str_input == "");


        do
        {


            std::stringstream ss(str_input);



            if (load_in_prog)
            {
                // starts when load is in progress
                // starts parsing input text file should from this point onward. parses the input line back into the cmd_input
                cmd_input.clear();
                ss.str("");
                ss << cmd_output[0];
                cmd_output.erase(cmd_output.begin()); //pop off first line
            }


            // modified code from example at https://stackoverflow.com/questions/8046357/how-do-i-check-if-a-stringstream-variable-is-empty-null/36327567
            // adds each word from cmd invidually to a vector while the stringstream buffer is not equal to 0
            while (ss.rdbuf()->in_avail() != 0)
            {
                std::getline(ss, cmd, ' ');
                cmd_input.push_back(cmd);
            }

            // parsing input
            if (cmd_input[0] == "exit")
            {
                cmd_input.erase(cmd_input.begin()); //pop off first command
                exit_program = exit_fun(cmd_input);

            }
            else if (cmd_input[0] == "load")
            {
                cmd_input.erase(cmd_input.begin()); //pop off first command
                //  text.txt left
                if (cmd_input.size() == 1)
                {
                    load_file(cmd_input, cmd_output);
                    cmd_input.clear();
                    load_in_prog = true; // important for progam flow
                    finished_load = false;//imp
                }
                else
                {
                    std::cout << "\nLoad error\n";
                }
                cmd_input.clear();
            }
            else if (cmd_input[0] == "register" && !simulate)
            {
                std::shared_ptr<Node> tmp_pointer = nullptr;

                cmd_input.erase(cmd_input.begin()); //pop off first command
                //<task>[0] <priority>[0] <length>[2] <arrives>[3] 
                tmp_pointer = std::make_shared<Node>(cmd_input[0], std::stoi(cmd_input[1]), std::stoi(cmd_input[2]), std::stoi(cmd_input[3]));
                list.push_back(tmp_pointer);

            }
            else if (cmd_input[0] == "remove" && !simulate)
            {


                cmd_input.erase(cmd_input.begin()); //pop off first command
                //<name>[0]
                for (unsigned int i = 0; i < list.size(); i++)
                {
                    if (list[i]->task_name == cmd_input[0])
                    {
                        list.erase(list.begin() + i);
                    }
                }

            }
            else if (cmd_input[0] == "display" && simulate)
            {
                std::cout << "\n TIME: " << sim_time << "\n";
                std::cout << " ACTIVE TASK: \n";

                if (active_task != nullptr)
                {
                    std::cout << active_task->task_name << "\t" << active_task->priority << "\t   ";
                    std::cout << active_task->start_time << "\t   " << active_task->length << "\n";
                }
                std::cout << " PRIORITYY QUEUE: \n";
                std::cout << " Name   Priority StartTime Length\n";
                for (std::shared_ptr<Node> n : heap)
                {
                    std::cout << n->task_name << "\t" << n->priority << "\t   ";
                    std::cout << n->start_time << "\t   " << n->length << "\n";
                }
            }
            else if (cmd_input[0] == "display" && !simulate)
            {
                std::cout << "\n LIST:\n";
                std::cout << " Name   Priority StartTime Length\n";
                for (std::shared_ptr<Node> n : list)
                {
                    std::cout << n->task_name << "\t" << n->priority << "\t   ";
                    std::cout << n->start_time << "\t   " << n->length << "\n";
                }
            }
            else if (cmd_input[0] == "clear" && !simulate)
            {


                cmd_input.erase(cmd_input.begin()); //pop off first command

                // set each pointer to null
                

                // remove all spaces in vector

                for (unsigned int i = 0; i < list.size(); i++)
                {
                    list[i] = nullptr;
                    
                }

                int list_size = list.size();
                for (unsigned int i = 0; i < list_size; i++)
                {
                    list.pop_back();
                }



            }
            else if (cmd_input[0] == "simulate" && list.size() != 0)
            {
                // set mode
                simulate = true;
                std::cout << "\n" <<"Simulation Mode <<<<<<<<\n";
                // move all events from list to heap
                for (std::shared_ptr<Node> n : list)
                {
                    n->refresh();
                    heap.push_back(n);
                }
                // make vector into heap
                std::make_heap(heap.begin(), heap.end(), cmp_starttime);

            }
            else if (cmd_input[0] == "schedule")
            {

                simulate = false;
                std::cout << "\n" << " Schedule Mode \n";

            }
            else if (cmd_input[0] == "step" && simulate)
            {
                cmd_input.erase(cmd_input.begin()); //pop off first command

                if (cmd_input.size() > 0)
                {
                    bool active_task_NULL = true; // cant set pointers to null
                    int steps = std::stoi(cmd_input[0]);
                    int sim_stop_time = sim_time + steps;
                    for (sim_time; sim_time < sim_stop_time; sim_time++)
                    {

                        // intializes if sim time is 0 
                        if (active_task == nullptr && (!heap.empty() && sim_time == 0))
                        {
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // sets active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }

                        // peak the top of the heap. if higher priority replace
                        if (!heap.empty() && cmp_starttime(active_task, heap.front()))
                        {
                            //push active_task back into heap
                            heap.push_back(active_task);
                            // remakes heap
                            std::push_heap(heap.begin(), heap.end(), cmp_starttime);
                            // pop higest priority task off heap
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // replace active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }

                        if (active_task != nullptr && active_task->start_time <= sim_time)
                        {
                            active_task->elapsed_time += 1;
                        }
                        // check to see if task is complete

                        if (active_task != nullptr && active_task->elapsed_time == active_task->length)
                        {// task is finished remove
                            std::cout << "\n ACTIVE TASK HAS COMPLETED \n";
                            std::cout << "Name:  Priority: StartTime:  Length:\n";
                            std::cout << active_task->task_name << "\t" << active_task->priority << "\t ";
                            std::cout << active_task->start_time << "\t" << active_task->length << "\n";
                            //delete active_task; 
                            // dont need to delete
                            active_task = nullptr;
                        }

                        // replaces active task for next step
                        if (active_task == nullptr && !heap.empty())
                        {
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // sets active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }
                    }
                }
                else
                {
                    int steps = 1;
                    int sim_stop_time = sim_time + steps;
                    for (sim_time; sim_time < sim_stop_time; sim_time++)
                    {

                        // intializes if sim time is 0 
                        if (active_task == nullptr && (!heap.empty() && sim_time == 0))
                        {
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // sets active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }

                        // peak the top of the heap. if higher priority replace
                        if (!heap.empty() && cmp_starttime(active_task, heap.front()))
                        {
                            //push active_task back into heap
                            heap.push_back(active_task);
                            // remakes heap
                            std::push_heap(heap.begin(), heap.end(), cmp_starttime);
                            // pop higest priority task off heap
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // replace active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }

                        if (active_task != nullptr && active_task->start_time <= sim_time)
                        {
                            active_task->elapsed_time += 1;
                        }
                        // check to see if task is complete

                        if (active_task != nullptr && active_task->elapsed_time == active_task->length)
                        {// task is finished remove
                            std::cout << "\n ACTIVE TASK HAS COMPLETED \n";
                            std::cout << "Name:  Priority: StartTime:  Length:\n";
                            std::cout << active_task->task_name << "\t" << active_task->priority << "\t ";
                            std::cout << active_task->start_time << "\t" << active_task->length << "\n";
                            //delete active_task; 
                            // dont need to delete
                            active_task = nullptr;
                        }

                        // replaces active task for next step
                        if (active_task == nullptr && !heap.empty())
                        {
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // sets active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }


                    }
                }

                // print results 
                std::cout << "\nCURRENT STATUS <<<<<<<<<<<<<<";
                std::cout << "\nTIME: " << sim_time << "\n";
                std::cout << "\nACTIVE TASK:\n";

                if (active_task != nullptr)
                {
                    std::cout << active_task->task_name << "\t" << active_task->priority << "\t";
                    std::cout << active_task->start_time << "\t" << active_task->length << "\n";
                }
                std::cout << " \nPRIORITYY QUEUE: \n";
                std::cout << "Name   Priority StartTime Length\n";
                for (std::shared_ptr<Node> n : heap)
                {
                    std::cout << n->task_name << "\t" << n->priority << "\t      ";
                    std::cout << n->start_time << "\t      " << n->length << "\n";
                }


            }
            else if (cmd_input[0] == "run" && !simulate)
            {
                std::cout << "\nRUN ONLY APPLIES IN SIMULATE MODE <<<<<<<<<<<\n";
            }
            else if (cmd_input[0] == "run" && simulate)
            {
                cmd_input.erase(cmd_input.begin()); //pop off first command

                //run - run the simulation until the last task has completed.
                       //empty
                if (cmd_input.size() == 0)
                {
                    bool active_task_bool = true;
                    while (active_task_bool)
                    {
                        // intializes if sim time is 0 
                        if (active_task == nullptr && (!heap.empty() && sim_time == 0))
                        {
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // sets active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }

                        // peak the top of the heap. if higher priority replace
                        if (!heap.empty() && cmp_starttime(active_task, heap.front()))
                        {
                            //push active_task back into heap
                            heap.push_back(active_task);
                            // remakes heap
                            std::push_heap(heap.begin(), heap.end(), cmp_starttime);
                            // pop higest priority task off heap
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // replace active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }
                        // elapsed time counts towards completing task
                        if (active_task != nullptr && active_task->start_time <= sim_time)
                        {
                            active_task->elapsed_time += 1;
                        }
                        // check to see if task is complete

                        if (active_task != nullptr && active_task->elapsed_time == active_task->length)
                        {// task is finished remove

                            std::cout << "\nACTIVE TASK HAS COMPLETED <<<<<<<<< \n";
                            std::cout << "\nTIME: " << sim_time << "\n";
                            std::cout << "Name:  Priority: StartTime:  Length:\n";
                            std::cout << active_task->task_name << "\t" << active_task->priority << "\t ";
                            std::cout << active_task->start_time << "\t" << active_task->length << "\n";
                            
                            active_task = nullptr;
                            if (active_task == nullptr && heap.empty())
                            {
                                active_task_bool = false;
                            }
                        }

                        // replaces active task for next step
                        if (active_task == nullptr && !heap.empty())
                        {
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // sets active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }

                        sim_time++;
                    }

                }
                else  //til[0] <time>[1]
                {
                    while (sim_time < std::stoi(cmd_input[1]))
                    {
                        // intializes if sim time is 0 
                        if (active_task == nullptr && (!heap.empty() && sim_time == 0))
                        {
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // sets active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }

                        // peak the top of the heap. if higher priority replace
                        if (!heap.empty() && cmp_starttime(active_task, heap.front()))
                        {
                            //push active_task back into heap
                            heap.push_back(active_task);
                            // remakes heap
                            std::push_heap(heap.begin(), heap.end(), cmp_starttime);
                            // pop higest priority task off heap
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // replace active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }
                        // elapsed time counts towards completing task
                        if (active_task != nullptr && active_task->start_time <= sim_time)
                        {
                            active_task->elapsed_time += 1;
                        }
                        // check to see if task is complete

                        if (active_task != nullptr && active_task->elapsed_time == active_task->length)
                        {// task is finished remove

                            std::cout << "\nACTIVE TASK HAS COMPLETED <<<<<<<<< \n";
                            std::cout << "\nTIME: " << sim_time << "\n";
                            std::cout << "Name:  Priority: StartTime:  Length:\n";
                            std::cout << active_task->task_name << "\t" << active_task->priority << "\t ";
                            std::cout << active_task->start_time << "\t" << active_task->length << "\n";
                            
                            active_task = nullptr;
                        }

                        // replaces active task for next step
                        if (active_task == nullptr && !heap.empty())
                        {
                            //moves task with highest priority to back
                            std::pop_heap(heap.begin(), heap.end(), cmp_starttime);
                            // sets active_task to highest priority task
                            active_task = heap.back();
                            // deletes highest priority task from heap
                            heap.pop_back();
                        }

                        sim_time++;
                    }
                }

                // print results 
                std::cout << "\nCURRENT STATUS <<<<<<<<<<<<<<";
                std::cout << "\nTIME: " << sim_time << "\n";
                std::cout << "\nACTIVE TASK:\n";

                if (active_task != nullptr)
                {
                    std::cout << active_task->task_name << "\t" << active_task->priority << "\t";
                    std::cout << active_task->start_time << "\t" << active_task->length << "\n";
                }
                std::cout << " \nPRIORITYY QUEUE: \n";
                std::cout << "Name   Priority StartTime Length\n";
                for (std::shared_ptr<Node> n : heap)
                {
                    std::cout << n->task_name << "\t" << n->priority << "\t      ";
                    std::cout << n->start_time << "\t      " << n->length << "\n";
                }



            }
            else if (cmd_input[0] == "reset" && simulate)
            {
                sim_time = 0;

                // empty heap

                if (!heap.empty())
                {
                    for (int i = 0; i < heap.size(); i++)
                    {
                        heap.pop_back();

                    }
                }

               



            }
            else
            {
                std::cout << "Undefined CALLED or Mode is incorrect \n";
            }


            finished_load = cmd_output.empty();


            if (finished_load)
            {
                load_in_prog = false;
            }

            // clear cmd_input at begining of program
        } while (finished_load == false);



    } while (exit_program == false);
}