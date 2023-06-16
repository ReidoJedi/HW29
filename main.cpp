void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;
    newNode->node_mutex = new std::mutex;

    Node* prev = nullptr;
    Node* curr = head;

    // Traverse to the desired position or the end of the list
    int i = 0;
    while (curr != nullptr && i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    // Lock the previous node's mutex
    std::lock_guard<std::mutex> prevLock(*(prev->node_mutex));

    // Check if we reached the end of the list
    if (curr == nullptr) {
        prev->next = newNode;
    }
    else {
        // Lock the current node's mutex
        std::lock_guard<std::mutex> currLock(*(curr->node_mutex));

        // Update the pointers to insert the new node
        newNode->next = curr;
        prev->next = newNode;
    }
}
