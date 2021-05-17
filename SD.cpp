#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
//#include <unistd.h>

using namespace std;

ifstream input_element("first_list.in"); //the file that contains the elements of the first list
ifstream input_secondary_elements("second_list.in"); //the file that contains the elements of the second list or a second wave of data for the first list
ifstream input_command("command_page.in"); //the file that contains the commands that the program needs to take in order to work
ofstream output_result("results.out"); //the file with the results from the commands


struct Element{ //The declaration of the element and it's values

    long long current_value;
    Element *next_element;
    Element *previous_element;
    Element *after_10;
    Element *before_10;
    //after_10 amd before_10 will be use as a skip, with the value of 10 elements, in functions, only some elements will have this value not NULL.
};



class Lista{ //The declaration of the list that will contain the elements we add with the structure above

    long long how_many_elements_are; // this variable will retain how many elements are in the list at any given time
    Element *first_element_in_queue; //this is the pointer for the first element in the list
    Element *last_element_in_queue; //this is the pointer for the last element in the list
    Element * the_one_how_gets; //this pointer will retain which element should get a non NULL value on the after_10 and before_10 pointers.
    char list_name[101]; //this name will serve as an id for the lists , there should not be 2 list with the same name.

public:

    Lista(char name_list[101]){
        this->first_element_in_queue=NULL;
        this->the_one_how_gets=NULL;
        this->last_element_in_queue=NULL;
        this->how_many_elements_are=0;
        strcpy(this->list_name,name_list);
    } // Constructor for our list, this will declare the pointers as NULL until they are assigned.

    Element* get_first_element_in_queue(){
        return first_element_in_queue;
    } // This getter will return the first element in the list

    Element* get_last_element_in_queue(){
        return last_element_in_queue;
    } // This getter will return the last element in the list

    char* get_name(){
        return list_name;
    } // This getter will return the name of the list

    void creating_the_skip_list(){

        long long current_position_in_list=1;
        Element *element_for_traversing_the_list=first_element_in_queue;

        while(element_for_traversing_the_list->next_element!=NULL){

            current_position_in_list++;
            element_for_traversing_the_list=element_for_traversing_the_list->next_element;

            if(current_position_in_list%10==0){
                the_one_how_gets->after_10=element_for_traversing_the_list;
                element_for_traversing_the_list->before_10=the_one_how_gets;
                the_one_how_gets=element_for_traversing_the_list;
            }
        }
    } //this function will create the skip list

    void insert_new_element(){

        output_result<<"How would you like to insert your new variables?\n1) Manually from console;\n2) Auto from a folder;\nYour variant:";
        int mode_for_inserting;

        while(true) {

            while (true) {
                if (input_command >> mode_for_inserting)
                    break;
                input_command.clear();
                input_command.ignore();
                output_result << "\nInvalid type for the input;\nPlease input a integer!\n\nYour command will be:";
            }

            int correct_value_for_inserting=1;

            if(mode_for_inserting!=1 and mode_for_inserting!=2)
                correct_value_for_inserting=0;
            if(correct_value_for_inserting==1)
                break;
        }// this while will verify the input correspond to one of the mods of inserting

        output_result<<mode_for_inserting<<'\n';

        if(mode_for_inserting==1) {

            int how_many_did_you_add = 0;
            cout << "\nInput a string value to stop inserting numbers!\n";

            while (true) {

                long long value_of_the_new_element;
                cout << "Please insert the value of the element you want to add:";
                int is_it_over = 0; //a variable to stop adding when the condition is met

                while (true) {
                    if (cin >> value_of_the_new_element)
                        break;
                    else {//if you input something of a different type then long long or int the session will end
                        is_it_over = 1;
                        cin.clear();
                        cin.ignore();
                        cout << "\nThe adding session is over\n";
                        break;
                    }
                }

                if (is_it_over == 1)
                    break;//stop point

                cout << '\n';

                Element *new_element = new Element;

                new_element->current_value = value_of_the_new_element;
                new_element->next_element = NULL;
                new_element->previous_element=NULL;
                new_element->after_10=NULL;
                new_element->before_10=NULL;//if the program did not stop, then we declared the new element we want to add to the list


                if (how_many_elements_are == 0) {

                    first_element_in_queue = new_element;
                    the_one_how_gets = new_element;
                }//condition if it's the first element we add to the list

                if (how_many_elements_are == 1){

                    if(new_element->current_value>first_element_in_queue->current_value){
                        last_element_in_queue=new_element;
                        first_element_in_queue->next_element=new_element;
                        new_element->previous_element=first_element_in_queue;
                    }
                    else{
                        first_element_in_queue->previous_element=new_element;
                        new_element->next_element=first_element_in_queue;
                        last_element_in_queue=first_element_in_queue;
                        first_element_in_queue=new_element;
                    }
                }//condition if it's the second element we add to the list

                if (how_many_elements_are > 1){

                    if(new_element->current_value>first_element_in_queue->current_value and new_element->current_value<last_element_in_queue->current_value) {

                        Element *element_for_verifying = first_element_in_queue;

                        while (element_for_verifying->next_element != NULL) {
                            if(element_for_verifying->after_10!=NULL and element_for_verifying->after_10->current_value<=new_element->current_value) {
                                element_for_verifying=element_for_verifying->after_10; //is using the skip list to get faster in the range of the element we want
                            }
                            else{
                                element_for_verifying=element_for_verifying->next_element;
                            }
                            if (new_element->current_value < element_for_verifying->current_value) {
                                break;
                            }
                        } //this while will find the position where to insert the new element using the skip list

                        Element *previous_element_after_verifying = element_for_verifying->previous_element;
                        previous_element_after_verifying->next_element = new_element;
                        element_for_verifying->previous_element = new_element;
                        new_element->previous_element = previous_element_after_verifying;
                        new_element->next_element = element_for_verifying;
                        //this block is inserting the element in the list

                    }


                    if(new_element->current_value>=last_element_in_queue->current_value){
                        new_element->previous_element=last_element_in_queue;
                        last_element_in_queue->next_element=new_element;
                        last_element_in_queue = new_element;

                    }//condition for being of value bigger or equal to the last element, so that will place the element as the last in queue
                    else{
                        if(new_element->current_value<=first_element_in_queue->current_value) {
                            new_element->next_element = first_element_in_queue;
                            first_element_in_queue->previous_element = new_element;
                            first_element_in_queue = new_element;
                        }
                    }//condition for being of value smaller or equal to the first element, so that will place the element as the first in queue
                }

                how_many_elements_are++;
                how_many_did_you_add++;

            }

            cout << "\nYou added " << how_many_did_you_add << " more elements to the list!\n";
        }

        if(mode_for_inserting==2){ //this mode is exactly the same steps, but instead of stopping when the program encounters a string value, for each character
            //a new value of 0 will be added to the list

            long long value_of_the_new_element,how_many_did_you_add=0;

            while(!input_element.eof()){

                while (true) {
                    if (input_element >> value_of_the_new_element)
                        break;
                    input_element.clear();
                    input_element.ignore();
                    break;
                }

                Element *new_element = new Element;

                new_element->current_value = value_of_the_new_element;
                new_element->next_element = NULL;
                new_element->previous_element=NULL;
                new_element->after_10=NULL;
                new_element->before_10=NULL;


                if (how_many_elements_are == 0) {

                    first_element_in_queue = new_element;
                    the_one_how_gets = new_element;
                }

                if (how_many_elements_are == 1){

                    if(new_element->current_value>first_element_in_queue->current_value){
                        last_element_in_queue=new_element;
                        first_element_in_queue->next_element=new_element;
                        new_element->previous_element=first_element_in_queue;
                    }
                    else{
                        first_element_in_queue->previous_element=new_element;
                        new_element->next_element=first_element_in_queue;
                        last_element_in_queue=first_element_in_queue;
                        first_element_in_queue=new_element;
                    }
                }

                if (how_many_elements_are > 1){

                    if(new_element->current_value>first_element_in_queue->current_value and new_element->current_value<last_element_in_queue->current_value) {

                        Element *element_for_verifying = first_element_in_queue;

                        while (element_for_verifying->next_element != NULL) {
                            if(element_for_verifying->after_10!=NULL and element_for_verifying->after_10->current_value<=new_element->current_value) {
                                element_for_verifying=element_for_verifying->after_10; //is using the skip list to get faster in the range of the element we want
                            }
                            else{
                                element_for_verifying=element_for_verifying->next_element;
                            }
                            if (new_element->current_value < element_for_verifying->current_value) {
                                break;
                            }
                        }

                        Element *previous_element_after_verifying = element_for_verifying->previous_element;
                        previous_element_after_verifying->next_element = new_element;
                        element_for_verifying->previous_element = new_element;
                        new_element->previous_element = previous_element_after_verifying;
                        new_element->next_element = element_for_verifying;

                    }


                    if(new_element->current_value>=last_element_in_queue->current_value){
                        new_element->previous_element=last_element_in_queue;
                        last_element_in_queue->next_element=new_element;
                        last_element_in_queue = new_element;

                    }
                    else {
                        if (new_element->current_value <= first_element_in_queue->current_value) {

                            new_element->next_element = first_element_in_queue;
                            first_element_in_queue->previous_element = new_element;
                            first_element_in_queue = new_element;

                        }
                    }
                }

                how_many_elements_are++;
                how_many_did_you_add++;
            }
            output_result<<"You added "<<how_many_did_you_add<<" more elements in "<<list_name<<"\n";
        }
    } //This function will insert new elements in the current list in a growing manner

    void delete_element(long long element){

        if(how_many_elements_are>0) {

            Element *current_element = first_element_in_queue;
            int in_queue = 0;

            if(element==last_element_in_queue->current_value){
                last_element_in_queue=last_element_in_queue->previous_element;
                last_element_in_queue->next_element->previous_element=NULL;
                last_element_in_queue->next_element=NULL;
                last_element_in_queue->after_10=NULL;
                last_element_in_queue->before_10=NULL;
                output_result << "Element deleted successfully\n";
                how_many_elements_are--;
            }
            else{
                while (current_element->next_element != NULL) {
                    if (current_element->after_10 != NULL and current_element->after_10->current_value <= element) {
                        current_element = current_element->after_10;//is using the skip list to get faster in the range of the element we want
                    }
                    else {
                        if (current_element->current_value == element) {
                            in_queue = 1;
                            break;
                        }
                        current_element = current_element->next_element;
                    }
                }

                if (in_queue == 1) {
                    if (current_element!= first_element_in_queue){
                        current_element->previous_element->next_element = current_element->next_element;
                        current_element->next_element->previous_element = current_element->previous_element;
                        current_element->after_10=NULL;
                        current_element->before_10=NULL;
                    }
                    else{
                        first_element_in_queue=first_element_in_queue->next_element;
                        first_element_in_queue->previous_element->next_element=NULL;
                        first_element_in_queue->previous_element=NULL;
                        current_element->after_10=NULL;
                        current_element->before_10=NULL;
                    }
                    output_result << "Element deleted successfully\n";

                    how_many_elements_are--;

                }// this if will delete the element in both ways, in the previous and in the next, if there is a next or a previous
                else
                    output_result<<"The element you want to delete is not in the list\n";
            }
        }
        else{
            output_result<<"There are no elements\n";
        }
    } //This function will delete any element from the list , if it is present

    void the_smallest_element(){

        if(how_many_elements_are>0)
            output_result<<"Minim:"<<first_element_in_queue->current_value<<'\n';
        else
            output_result<<"There are no elements\n";
    } //This function will print the smallest element in the list

    void the_biggest_element(){
        if(how_many_elements_are>0)
            output_result<<"Maxim:"<<last_element_in_queue->current_value<<'\n';
        else
            output_result<<"There are no elements\n";
    } //This function will print the largest element in the list

    void the_next_element(long long element){
        if(how_many_elements_are>0){

            Element *the_smallest_big;
            Element *current_element=first_element_in_queue;
            bool was_found_one=false;

            if(element>=last_element_in_queue->current_value){
                output_result<<"There was no element bigger than "<<element<<'\n';
            }
            else{
                while(current_element->next_element!=NULL){

                    if(current_element->after_10!=NULL and current_element->after_10->current_value<=element) {
                        current_element=current_element->after_10;//is using the skip list to get faster in the range of the element we want
                    }
                    else {

                        if (current_element->current_value > element) {
                            the_smallest_big = current_element;
                            was_found_one = true;
                        }
                        if(was_found_one==true)
                            break;
                        current_element = current_element->next_element;
                    }
                }
                output_result<<"Successor:"<<the_smallest_big->current_value<<'\n';
            }
        }
        else{
            output_result<<"There are no elements\n";
        }
    } //This function will show if there is a element larger then the number you enter

    void the_element_before(long long element){

        if(how_many_elements_are>0){

            Element *the_biggest_small;
            Element *current_element=last_element_in_queue;
            bool was_found_one=false;

            if(element<=first_element_in_queue->current_value){
                output_result<<"There was no element smaller than "<<element<<'\n';
            }
            else{
                while(current_element->previous_element!=NULL) {

                    if(current_element->before_10!=NULL and current_element->before_10->current_value>=element) {
                        current_element=current_element->before_10;//is using the skip list to get faster in the range of the element we want
                    }
                    else {

                        if (current_element->current_value < element) {
                            the_biggest_small = current_element;
                            was_found_one = true;
                        }
                        if(was_found_one==true)
                            break;
                        current_element = current_element->previous_element;
                    }
                }
                output_result<<"Predecessor:"<<the_biggest_small->current_value<<'\n';
            }
        }
        else{
            output_result<<"There are no elements\n";
        }

    } //This function will show if there is a element smaller then the number you enter

    void the_k_element(long long k){

        //in function of how many elements there are, how big k is and we'll use the fact that the list in arranged in a growing manner.
        //we will divide the list in 2 equal parts and we will try to find k in the respective half
        //there are 2 special cases , if k is first or last element , then the program will print the respective part, and one
        // if the k is bigger then the number of elements in the list, then the program will print a message that there is not an k element

        if(k>how_many_elements_are/2 and k<how_many_elements_are){

            long long current_position=how_many_elements_are;
            Element *current_element=last_element_in_queue;

            while(current_position>k){
                current_position--;
                current_element=current_element->previous_element;
            }

            output_result<<"The k element:"<<current_element->current_value<<'\n';
        }

        if(k<=how_many_elements_are/2 and k>1){

            long long current_position=1;
            Element *current_element=first_element_in_queue;

            while(current_position<k){
                current_position++;
                current_element=current_element->next_element;
            }

            output_result<<"The k element:"<<current_element->current_value<<'\n';
        }

        if(k==how_many_elements_are){
            output_result<<"The k element:"<<last_element_in_queue->current_value<<'\n';
        }

        if(k==1){
            output_result<<"The k element:"<<first_element_in_queue->current_value<<'\n';
        }

        if(k>how_many_elements_are){
            output_result<<"There are not enough elements in the list\n";
        }
    } //This function will print the k element in the list, if there are k or more elements in this list

    long long get_how_many_elements(){
        return how_many_elements_are;
    } //This will return the number of elements the list contains

    bool is_in_queue(long long element){

        Element *current_element = first_element_in_queue;
        if(first_element_in_queue->current_value==element or last_element_in_queue->current_value==element) {
            output_result << "Is in queue\n";
            return true; //if the element is found, return true
        }
        if(first_element_in_queue->current_value>element or last_element_in_queue->current_value<element) {
            output_result << "Is doesn't appear in the queue\n";
            return false;
        }
        while (current_element != NULL) {
            if(current_element->after_10!=NULL and current_element->after_10->current_value<element) {
                current_element=current_element->after_10; //is using the skip list to get faster in the range of the element we want
            }
            else {
                current_element = current_element->next_element;
                if (current_element->current_value == element) {
                    output_result << "Is in queue\n";
                    return true; //if the element is found, return true
                }
                if(current_element->current_value>element){
                    break;
                }
            }
        }

        output_result << "Is doesn't appear in the queue\n";
        return false; //if the code is here, that means that the element was not in the list, so return false.

    } //This will print if the element you introduce is in the list

    void showcase_elements(Element *element){

        if(how_many_elements_are>0){
            output_result<<element->current_value<<" ";
            if (element->next_element != NULL)
                showcase_elements(element->next_element); //a recursive function for printing all the elements
        }
        else{
            output_result<<"There are no elements";
        }
    } //This will print all the elements in the list

    void input_for_second_list(){
        long long value_of_the_new_element,how_many_did_you_add=0;

        while(!input_secondary_elements.eof()) {

            while (true) {
                if (input_secondary_elements >> value_of_the_new_element)
                    break;
                input_secondary_elements.clear();
                input_secondary_elements.ignore();
                break;
            }

            Element *new_element = new Element;

            new_element->current_value = value_of_the_new_element;
            new_element->next_element = NULL;
            new_element->previous_element = NULL;
            new_element->after_10 = NULL;
            new_element->before_10 = NULL;


            if (how_many_elements_are == 0) {

                first_element_in_queue = new_element;
                the_one_how_gets = new_element;
            }

            if (how_many_elements_are == 1) {

                if (new_element->current_value > first_element_in_queue->current_value) {
                    last_element_in_queue = new_element;
                    first_element_in_queue->next_element = new_element;
                    new_element->previous_element = first_element_in_queue;
                } else {
                    first_element_in_queue->previous_element = new_element;
                    new_element->next_element = first_element_in_queue;
                    last_element_in_queue = first_element_in_queue;
                    first_element_in_queue = new_element;
                }
            }

            if (how_many_elements_are > 1) {

                if (new_element->current_value > first_element_in_queue->current_value and
                    new_element->current_value < last_element_in_queue->current_value) {

                    Element *element_for_verifying = first_element_in_queue;

                    while (element_for_verifying->next_element != NULL) {
                        if (new_element->current_value < element_for_verifying->current_value) {
                            break;
                        }
                        element_for_verifying = element_for_verifying->next_element;
                    }

                    Element *previous_element_after_verifying = element_for_verifying->previous_element;
                    previous_element_after_verifying->next_element = new_element;
                    element_for_verifying->previous_element = new_element;
                    new_element->previous_element = previous_element_after_verifying;
                    new_element->next_element = element_for_verifying;

                }


                if (new_element->current_value >= last_element_in_queue->current_value) {
                    new_element->previous_element = last_element_in_queue;
                    last_element_in_queue->next_element = new_element;
                    last_element_in_queue = new_element;

                } else {
                    if (new_element->current_value <= first_element_in_queue->current_value) {

                        new_element->next_element = first_element_in_queue;
                        first_element_in_queue->previous_element = new_element;
                        first_element_in_queue = new_element;

                    }
                }
            }

            how_many_elements_are++;
            how_many_did_you_add++;
        }
        output_result<<"You added "<<how_many_did_you_add<<" more elements in "<<list_name<<"\n";
    }//This will insert elements from a different folder then the first one you accessed when you inserted the elements in your list first time
};

vector<Lista> data_for_program; //The vector will retain the List as an element so you will be able to have more List with different data in each of them at the same time
long long how_much_data; //This variable will retain the number of elements in the vector

class menu{
public:

    void command_1(){

        char name_list[101];

        while(true){

            output_result<<"Name the list:";
            input_command>>name_list;
            output_result<<name_list<<'\n';
            int name_is_ok=1;

            for(long long i=0;i<how_much_data;i++){
                if(strcmp(data_for_program[i].get_name(),name_list)==0){
                    name_is_ok=0;
                    cout<<"\nName already in use\n";
                    break;
                }
            }

            if(name_is_ok==1)
                break;
        } //this while will make sure the name is unique to every list created so it can be used as an id, after this the new list will be created and added to the vector

        Lista A(name_list);
        data_for_program.push_back(A);
        how_much_data++;

    } //Create list

    void command_2(Lista &lista, Lista &lista2){

        if(strcmp(lista.get_name(),lista2.get_name())==0)
            output_result<<"You are already in this list!\n";
        else{
            swap(lista, lista2);
            output_result<<"You have successfully transferred to "<<lista.get_name()<<'\n';
        }
    } //Change current list; this command will use the function swap, to interchange every element of the

    void command_3(Lista &lista){
        lista.insert_new_element();
        lista.creating_the_skip_list();
    } //Insert element , will call the class function for inserting elements in the current list

    void command_4(Lista &lista){
        lista.the_smallest_element();
    } //Minim of the current list , will call the class function for printing the minim (which is the first element in the list because of how the elements are inserted)

    void command_5(Lista &lista){
        lista.the_biggest_element();
    } //Maxim of the current list , will call the class function for printing the maxim (which is the last element in the list because of how the elements are inserted)

    void command_6(Lista &lista){
        lista.showcase_elements(lista.get_first_element_in_queue());
    } //Showcase elements of the current list ,will call the class function for printing the elements in the list

    void command_7(Lista &lista,long long  number){
        lista.is_in_queue(number);
    } //Is in the current list? ,will call the class function for finding if an element is in the list or not

    void command_8(Lista &lista,long long  number){
        lista.delete_element(number);
    } //Delete from the current list ,will call the class function for deleting an element, if it is in the list

    void command_9(Lista &lista,long long  number){
        lista.the_k_element(number);
    } //The K element ,will call the class function for finding what is the k element in the list, as value

    void command_10(Lista &lista,long long  number){
        lista.the_next_element(number);
    } //Next element from x , will call the class function for finding and printing a larger element then the one you input

    void command_11(Lista &lista,long long number){
        lista.the_element_before(number);
    } //Previous element from x , will call the class function for finding and printing a smaller element then the one you input

    void command_12(Lista &lista){
        output_result<<"Results:\n"<<lista.get_name();
        output_result<<"\n"<<&lista<<'\n';
    } //Name and memory place of the current list, will print out the returned value of the function get_name()
    // then will show the memory space where the current list is stored

    void command_13(Lista &lista){
        output_result<<"Results:\n"<<lista.get_how_many_elements()<<'\n';
    } //How many elements are in the current list , will print the returned value of the function get_how_many_elements()

    void command_14(Lista &lista){
        lista.input_for_second_list();
        lista.creating_the_skip_list();
    }//This command will access the elements in a different folder so you can add more elements in your list, or in a new list
};

void presentation(){
    cout<<"""\n"
          " 1. Create list\n"
          " 2. Change current list\n"
          " 3. Insert element\n"
          " 4. Minim of the current list\n"
          " 5. Maxim of the current list\n"
          " 6. Showcase elements of the current list\n"
          " 7. Is in the current list?\n"
          " 8. Delete from the current list\n"
          " 9. The K element\n"
          " 10. Next element from x\n"
          " 11. Previous element from x\n"
          " 12. Name and memory place of the current list\n"
          " 13. How many elements are in the current list\n"
          " 14. Input elements for a new list from a new folder\n"
          " 0. Exit""";
    output_result<<"\nInput a command:";
} //A function to print out the options of the menu

int command;

int main(){

    menu Meniu; // creating the variable that will represent the menu of the program
    Lista prima_lista((char*)"prima lista"); //creating a default list
    Lista current_list=prima_lista; //Declaring the default list as the current list
    data_for_program.push_back(prima_lista); //Adding the list to the vector
    how_much_data++; //Increasing the data number in the vector
    long long number;

    presentation(); //printing the menu

    while(true){ //until 0 is entered as a command this while will take an infinite amount of commands for the program

        output_result<<"Command:";

        while(true){
            if(input_command>>command)
                break;
            input_command.clear();
            input_command.ignore();
            output_result<<"\nInvalid type for the input;\nPlease input a integer!\n\nYour command will be:";
        } // This while will make sure that the command the user inputs is of the correct type
        // from there every number will link to the corresponding function in the menu class
        // To the commands that need a bonus input, the a version of the while above will be implemented to ensure that the command will work properly

        output_result<<command<<'\n';

        if(command==0){
            output_result<<"Bye!";
            break;
        } //break condition

        if(command==1) {
            Meniu.command_1();
        }

        if(command==2) {

            output_result<<"You are in "<<current_list.get_name()<<"\n";
            int input_position_for_new_list=-1;

            for(long long i=1;i<how_much_data;i++){
                output_result<<i<<". "<<data_for_program[i].get_name()<<'\n';
            }

            while(true){

                input_command>>input_position_for_new_list;
                if(input_position_for_new_list>0 and input_position_for_new_list<=how_much_data)
                    break;
                else
                    output_result<<"Invalid position, please insert a number of a list:";
            }

            Meniu.command_2(current_list,data_for_program[input_position_for_new_list]);
        }

        if(command==3){
            Meniu.command_3(current_list);
        }

        if(command==4) {
            Meniu.command_4(current_list);
        }

        if(command==5){
            Meniu.command_5(current_list);
        }

        if(command==6){
            output_result<<'\n';
            Meniu.command_6(current_list);
            output_result<<'\n';
        }

        if(command==7){
            if(current_list.get_how_many_elements()>0){

                output_result<<"Input a number:";

                while(true){
                    if(input_command>>number)
                        break;
                    input_command.clear();
                    input_command.ignore();
                    output_result<<"\nInvalid type for the input;\nPlease input a integer!\n\nYour number will be:";
                }

                output_result<<number<<'\n';

                Meniu.command_7(current_list,number);
            }
            else{
                output_result<<"There is nothing";
            }
        }

        if(command==8){
            if (current_list.get_how_many_elements() > 0){

                output_result << "Input a number:";

                while(true){
                    if(input_command>>number)
                        break;
                    input_command.clear();
                    input_command.ignore();
                    output_result<<"\nInvalid type for the input;\nPlease input a integer!\n\nYour number will be:";
                }

                output_result<<number<<'\n';

                Meniu.command_8(current_list, number);
            }
            else{
                output_result<<"There is nothing";
            }
        }

        if(command==9){
            if(current_list.get_how_many_elements()>0){

                output_result << "Input a number:";

                while(true){
                    if(input_command>>number)
                        break;
                    input_command.clear();
                    input_command.ignore();
                    output_result<<"\nInvalid type for the input;\nPlease input a integer!\n\nYour number will be:";
                }

                output_result<<number<<'\n';

                Meniu.command_9(current_list, number);
            }
            else{
                output_result<<"There is nothing";
            }
        }

        if(command==10){
            if(current_list.get_how_many_elements()>0){

                output_result << "Input a number:";

                while(true){
                    if(input_command>>number)
                        break;
                    input_command.clear();
                    input_command.ignore();
                    output_result<<"\nInvalid type for the input;\nPlease input a integer!\n\nYour number will be:";
                }

                output_result<<number<<'\n';

                Meniu.command_10(current_list, number);
            }
            else{
                output_result<<"There is nothing";
            }
        }

        if(command==11){
            if(current_list.get_how_many_elements()>0){
                output_result<<"Input a number:";
                while(true){
                    if(input_command>>number)
                        break;
                    input_command.clear();
                    input_command.ignore();
                    output_result<<"\nInvalid type for the input;\nPlease input a integer!\n\nYour number will be:";
                }

                output_result<<number<<'\n';

                Meniu.command_11(current_list,number);
            }
            else{
                output_result<<"There is nothing";
            }
        }

        if(command==12) {
            Meniu.command_12(current_list);
        }

        if(command==13) {
            Meniu.command_13(current_list);
        }

        if(command==14){
            Meniu.command_14(current_list);
        }

        if(command>14 or command<0) {
            output_result << "Invalid option";
        } //If the command is bigger or lower then what the menu will offer this if will print Invalid option

        //sleep(4);
        //system("clear");
    }
}
