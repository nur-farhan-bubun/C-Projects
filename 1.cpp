#include <iostream>
#include<string>
#include<memory>
#include <cstdint>
#include <cassert>
typedef struct Particles{

    int id;
    float x;
    float y;
    float z;
} Particle;

struct FreeNode{
    FreeNode* next;
};

class FixedSizeAllocator {
//how can i allocatte exactlly 16* 1000 byte memory?
private:
    static constexpr std::size_t OBJECT_SIZE = sizeof(Particle); 
    static constexpr std::size_t OBJECT_COUNT = 1000;
    static constexpr std::size_t TOTAL_BYTES = OBJECT_SIZE * OBJECT_COUNT; 
    std::unique_ptr<uint8_t[]> memory_block;
    FreeNode* head;
    public:
    FixedSizeAllocator() : memory_block(std::make_unique<uint8_t[]>(TOTAL_BYTES)), head(nullptr) {
        head = reinterpret_cast<FreeNode*>(memory_block.get());

    uint8_t* current_mem_block = memory_block.get();
  for(int i =0;i<OBJECT_COUNT-1;i++){
    FreeNode* current_node = reinterpret_cast<FreeNode*>(current_mem_block);
    current_mem_block = current_mem_block + OBJECT_SIZE;
    current_node->next = reinterpret_cast<FreeNode*>(current_mem_block);

    }
    FreeNode* last_node = reinterpret_cast<FreeNode*>(current_mem_block);
    last_node->next = nullptr;

    }
 //uintTestFortheCode
void VerifyFreeAllocationCode() const 
 {
    FreeNode *current = head;
    std::size_t count = 0;
    while(current != nullptr){
        count++;
     
       
        std::cout << "Node " << count << " at address: " << current << std::endl;
FreeNode* next_node = current->next;
 
 if(next_node != nullptr) {
    std::uintptr_t firstNode = reinterpret_cast<std::uintptr_t>(current);
    std::uintptr_t secondNode = reinterpret_cast<std::uintptr_t>(next_node);    
         if(secondNode - firstNode == OBJECT_SIZE){
              std::cout<<"Yes the Object Sizes are good"<<std::endl;

        } else {
            std::cout << "Object sizes are not right" << std::endl;
            return;
        }
    }
    std::cout << "Total nodes: " << count << std::endl;


 current = current->next;

 }

if (count == OBJECT_COUNT) {
        std::cout << "SUCCESS: Free list correctly created with " << OBJECT_COUNT << " nodes!" << std::endl;
    } else {
        std::cerr << "TEST FAILED: Expected " << OBJECT_COUNT << " nodes, got " << count << std::endl;
    }




 }

 Particle* allocate(){
    if(head == nullptr){
        std::cout<<"the Memory space is full"<<std::endl;
        return nullptr;
    }
 FreeNode* allocated_node = head;
 head = head->next;
 return reinterpret_cast<Particle*>(allocated_node);


 }

  void  freeMemory(Particle* ptr){
 if(ptr == nullptr){
    return;
 }
   FreeNode* freed_node = reinterpret_cast<FreeNode*>(ptr);
    freed_node->next = head;
 head =    freed_node ;

  }



};
 


void runUnitTest() {
    FixedSizeAllocator allocator;

   allocator.VerifyFreeAllocationCode(); 
    
    std::cout << "All Unit Tests Passed!" << std::endl;
}
int main() {
    runUnitTest();
    return 0;
}