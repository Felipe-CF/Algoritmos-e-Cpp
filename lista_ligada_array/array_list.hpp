#ifndef __ARRAY_LIST_IFRN__
#define __ARRAY_LIST_IFRN__


class array_list {
private:
    int* data;
    unsigned int size_, capacity_;
    void increase_capacity() {
        int* old_array = this->data;
        this->capacity_ = this->capacity_*2;
        int* new_array = new int[this->capacity_];
        for(unsigned int i = 0; i < this->capacity_; ++i){
            new_array[i] = old_array[i];
        }
        this->data = new_array;
        delete[] old_array;
    }
public:
    array_list() {
        data = new int[8];
        this->size_ = 0;
        this->capacity_ = 8;
    }
    ~array_list() {
        delete[] data;
    }
    unsigned int size() {
        return this->size_;
    }
    unsigned int capacity() {
        return this->capacity_;
    }
    double percent_occupied() {
        return static_cast<double>(size_)/capacity_;
    }
    
    bool insert_at(unsigned int index, int value) {
        if(index < this->size_){
            if(this->capacity_ == this->size_) this->increase_capacity();
            for(unsigned int i = size_; i > index; --i){
                data[i] = data[i-1];
            }
            this->data[index] = value;
            size_++;
            return true;
        }
        return false;
    }

    bool remove_at(unsigned int index) {
        if (index >= this->size_)
            return false; // Não removeu
        for (unsigned int i = index + 1; i < this->size_; ++i) {
            this->data[i-1] = this->data[i];
        }
        this->size_--;
        return true; // Removeu
    }

    int get_at(unsigned int index) {
        if(index < this->size_){
            return this->data[index];
        }
        return -1;
        // TODO: Check if index is valid
    }

    void clear() {
        if(size_ == 0) return;
        int *old_array;
        old_array = data;
 //       array_list();
        data = new int[8];
        this->size_ = 0;
        this->capacity_ = 8;
        delete[] old_array;
    }

    void push_back(int value) {
        if (this->size_ == this->capacity_)
            increase_capacity();
        this->data[size_++] = value;
    }

    void push_front(int value) {
        if(size_ == 0){
            data[size_++] = value;
            return;
        }
        if(size_ == capacity_) increase_capacity();
        for(unsigned int j = size_; j > 0; --j) data[j] = data[j-1];
        data[0] = value;
    }

    bool pop_back() {
        if(size_ > 0){
            int* array = new int[capacity_];
            for(unsigned int i = 0; i < size_-1; ++i)
                array[i] = data[i];
            int* remove = data;
            data = array;
            delete[] remove;
            size_--;
            return true;
        }
        return false;
    }

    bool pop_front() {
        if(size_ > 0){
            int* array = new int[capacity_];
            for(unsigned int i = 1; i < size_; ++i)
                array[i-1] = data[i];
            int* remove = data;
            data = array;
            delete[] remove;
            size_--;
            return true;
        }
        return false;
    }

    int front(){
        if(size_ == 0) return 0;
        return data[0];
    }

    int back(){
        if(size_ == 0) return 0;
        return data[size_-1];
    }

    bool remove(int value) {
        if(size_ != 0){
            for(unsigned int i = 0; i < size_; ++i){
                if(value == data[i]) {
                    for(unsigned int j = ++i; j < size_; ++j) data[j-1] = data[j];
                    size_--;
                    return true;                     
                }
            }
        }
        return false;
    }

    int find(int value) {
        if(size_ != 0){
            for(unsigned int i = 0; i < size_; ++i){
                if(value == data[i]) return true;
            }
        }
        return -1;
    }
    
    int count(int value) {
        int cont = 0;
        if(size_ != 0){
            for(unsigned int i = 0; i < size_; ++i){
                if(value == data[i]) cont++;
            }
        }
        return cont;
    }

    int sum() {
        int sum_ = 0;
        if(size_ != 0){
            for(unsigned int i = 0; i < size_; ++i) sum_ += data[i];
        }
        return sum_;
    }
    void print_list(){
        for(unsigned int i = 0; i < size_; ++i) std::cout << data[i] << " ";
    }
};

#endif // __ARRAY_LIST_IFRN__