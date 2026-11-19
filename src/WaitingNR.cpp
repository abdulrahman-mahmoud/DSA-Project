#include "include/WaitingNR.hpp"
#include "include/Queue.hpp"
#include "include/request.hpp"
#include "include/Node.hpp"

Request* WaitingNR::cancelByRID(int rid) {

    Node<Request*>* currentNode = front;
    Node<Request*>* historyNode = nullptr;

    while (currentNode != nullptr)
    {
        if (currentNode->data->getRID() == rid) {

            Request* foundRequest = currentNode->data;

            if (historyNode == nullptr) {
                front = currentNode->next;
            }
            else {
                historyNode->next = currentNode->next;
            }

            if (currentNode == rear) {
                rear = historyNode;
            }

            delete currentNode;
            count--;

            return foundRequest;
        }

        historyNode = currentNode;
        currentNode = currentNode->next;
    }

    return nullptr;
}