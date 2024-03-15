#ifndef __LINKED_LIST_IFRN__
#define __LINKED_LIST_IFRN__


class linked_list {
private:
    struct int_node {
        int value;
        int_node* next, * prev;
    };
    int_node* head, * tail;
    unsigned int size_;
public:
    linked_list() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size_ = 0;
    }
    ~linked_list() {
        int_node* current = this->head;
        while (current != nullptr) {
            int_node* to_remove = current;
            current = current->next;
            delete to_remove;
        }
    }

    unsigned int size() {
        return this->size_;
    }

    unsigned int capacitty() {
        return size();
    }

    double percent_occupied() {
        if (this->head == nullptr) return 0;
        return 1;
    }

    bool insert_at(unsigned int index, int value) {
        if(size_ == 0) {
            push_front(value);
            return true;
        }    
        if(index == 0){ 
            push_front(value);
            return true;
        }
        if(index == size_-1){
            push_back(value);
            return true;
        }
        else{
            int_node* current = this->head;
            while(index--) current = current->next;
            int_node* new_node = new int_node;
            new_node->value = value;
            new_node->prev = current->prev;
            current->prev->next = new_node;
            current->prev = new_node;
            new_node->next = current;
            size_++;
            return true;
        }
        return false;
    }

    bool remove_at(unsigned int index) {
        if (index >= this->size_)
            return false; // Não removeu
        int_node* to_remove = this->head;
        for (unsigned int i = 0; i < index; ++i)
            to_remove = to_remove->next;
        if (to_remove->prev != nullptr)
            to_remove->prev->next = to_remove->next;
        if (to_remove->next != nullptr)
            to_remove->next->prev = to_remove->prev;
        delete to_remove;
        size_--;
        return true; // Removeu
    }

    int get_at(unsigned int index) {
        if(this->head != nullptr){
            if(index < this->size()){
                int_node *current = new int_node;
                current = this->head;
                while(index--){
                    current = current->next;
                }
                return current->value;
            }
        }
        return -1;
    }

    void clear() {
        if(this->head == nullptr) return;
        int_node* current = this->head->next;
        while(current != nullptr){
            delete current->prev;
            current = current->next;
        }
        this->head = nullptr;
        this->tail = nullptr;
        this->size_ = 0; 
    }

    void push_back(int value) {
        int_node *new_node = new int_node;
        new_node->value = value;
        new_node->next = nullptr;
        new_node->prev = this->tail;
        if(this->head == nullptr) this->head = new_node; // lista vazia
        else this->tail->next = new_node;
        this->tail = new_node;
        this->size_++;
    }

    void push_front(int value) {
        int_node* new_node = new int_node;
        new_node->value = value;
        new_node->next = this->head;
        new_node->prev = nullptr;
        if (this->head == nullptr) this->tail = new_node;
        else this->head->prev = new_node;
        this->head = new_node;
        this->size_++;
    }

    bool pop_back() {
        if(this->tail == 0) return false;
        if(this->tail == this->head){
            delete this->tail;
            this->head = nullptr;
            this->tail = nullptr;
            return true;
        }
        int_node* to_remove = new int_node;
        to_remove = this->tail;
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
        delete to_remove;
        size_--;
        return true;
    }

    bool pop_front() {
        if(this->tail == 0) return false;
        if(this->tail == this->head){
            delete this->tail;
            this->head = nullptr;
            this->tail = nullptr;
            return true;
        }
        int_node* to_remove = new int_node;
        to_remove = this->head;
        this->head = this->head->next;
        this->head->prev = nullptr;
        delete to_remove;
        size_--;
        return true;
    }
    int front() {
        return this->head->value;
    }
    int back() {
        return this->tail->value;
    }
    bool remove(int value) {
        if(this->head != nullptr){
            if(this->head == this->tail){
                if(value == this->head->value){
                    delete this->head;
                    this->head = nullptr;
                    this->tail = nullptr;
                    return true;
                }
                return false;
            }
            int_node *current = this->head;
            while(current != nullptr){
                if(current->value == value){
                    int_node *remove = new int_node;
                    remove = current;
                    current->prev->next = remove->next;
                    current->next->prev = remove->prev;
                    current = current->next;
                    delete remove;
                    return true; 
                }
                current = current->next;
            }
        size_--;
        } 
        return false;
    }
    int find(int value) {
        if(this->head != nullptr){
            int_node *current = new int_node;
            current = this->head;
            int ind = 0;
            while(current != nullptr){
                if(current->value == value) return ind;
                current = current->next;
                ++ind;
            }
        }
        return -1;
    }

    int count(int value) {
        int count = 0;
        if(this->head != nullptr){
            int_node *current = this->head;
            while(current != nullptr){
                if(current->value == value) count++;
                current = current->next;
            }
        }
        return count;
    }

    int sum() {
       int sum = 0;
        if(this->head != nullptr){
            int_node *current = new int_node;
            current = this->head;
            while(current != nullptr){
                sum += current->value;
                current = current->next;
            }
        }
        return sum;
    }
    void print_list(){
        int_node* current = this->head;
        while(current != nullptr) {
            std::cout << " " << current->value;
            current = current->next;
        }
    }
};

#endif // __LINKED_LIST_IFRN__