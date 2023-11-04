//#include <gtest/gtest.h>
#include "priorityqueue.h"

/*TEST(priorityqueue, one) {
    // TO DO: write lots of assertions here.

}*/

void testingEnqueue1 () {
    priorityqueue<string> pq;

    pq.enqueue("Dolores", 5);
    pq.enqueue("Brenard", 4);
    pq.enqueue("Ford", 2);
    pq.enqueue("Arnold", 8);
    pq.enqueue("Jasmine", 6);
    pq.enqueue("Carlos", 11);

  cout << "\nTesting enqueue without duplicates:\n";
  cout << "Expected: 6\nRecieved: " << pq.Size() << endl;
  //pq.clear();
}

void testingEnqueue2 () {
  priorityqueue<string> pq;

    pq.enqueue("Dolores", 5);
    pq.enqueue("Joshua", 5);
    pq.enqueue("Brenard", 4);
    pq.enqueue("Ford", 2);
    pq.enqueue("Arnold", 8);
    pq.enqueue("Jasmine", 6);
    pq.enqueue("Carlos", 11);

  cout << "\nTesting enqueue with duplicates:\n";
  cout << "Expected: 7\nRecieved: " << pq.Size() << endl;
  //pq.clear();
}

void testingToString () {
  priorityqueue<string> pq;

    pq.enqueue("Dolores", 5);
    pq.enqueue("Joshua", 4);
    pq.enqueue("Brenard", 4);
    pq.enqueue("Ford", 2);
    pq.enqueue("Lei", 2);
    pq.enqueue("Wei", 2);
    pq.enqueue("Arnold", 8);
    pq.enqueue("Jasmine", 6);
    pq.enqueue("Carlos", 11);

  
  cout << "\nTesting enqueue with duplicates and using toString:\n";
  cout << "Expected: 9\nRecieved: " << pq.Size() << endl;
  cout << pq.toString();
  //pq.clear();
}

void testingEqualOperator () {

  cout << "Testing equal operator!\n";
  priorityqueue<string> pq;

    pq.enqueue("Dolores", 5);
    pq.enqueue("Joshua", 4);
    pq.enqueue("Brenard", 4);
    pq.enqueue("Ford", 2);
    pq.enqueue("Lei", 2);
    pq.enqueue("Wei", 2);
    pq.enqueue("Arnold", 8);
    pq.enqueue("Jasmine", 6);
    pq.enqueue("Carlos", 11);
  cout << "pq before being altered:\n\n";
  cout << pq.toString();
  
  priorityqueue<string> pq2;

    pq2.enqueue("Dolores", 5);
    pq2.enqueue("Joshua", 5);
    pq2.enqueue("Brenard", 4);
    pq2.enqueue("Ford", 2);
    pq2.enqueue("Arnold", 8);
    pq2.enqueue("Jasmine", 6);
    pq2.enqueue("Carlos", 11);
  cout << "pq2 this is the new pq values to be set\n\n";
  cout << pq2.toString();

  pq = pq2;

  cout << "pq after being updated to pq2:\n\n";
  cout << pq.toString();
}

void testingBeginandNext () {
  cout << "testing begin and next functions!\n\n\n";
  priorityqueue<string> pq2;
  string value;
  int priority;

    pq2.enqueue("Dolores", 5);
    pq2.enqueue("Joshua", 5);
    pq2.enqueue("Brenard", 4);
    pq2.enqueue("Ford", 2);
    pq2.enqueue("Arnold", 8);
    pq2.enqueue("Jasmine", 6);
    pq2.enqueue("Carlos", 11);

  pq2.begin();
    while (pq2.next(value, priority)) {
      cout << priority << " value: " << value << endl;
    }
    cout << priority << " value: " << value << endl;
}

void testingBeginandNext2 () {
  cout << "testing begin and next functions!\n\n\n";
  priorityqueue<string> pq2;
  string value;
  int priority;

    pq2.enqueue("Dolores", 5);
    pq2.enqueue("Joshua", 4);
    pq2.enqueue("Brenard", 4);
    pq2.enqueue("Ford", 2);
    pq2.enqueue("Lei", 2);
    pq2.enqueue("Wei", 2);
    pq2.enqueue("Arnold", 8);
    pq2.enqueue("Jasmine", 6);
    pq2.enqueue("Carlos", 11);

  pq2.toString();
  
  pq2.begin();
    while (pq2.next(value, priority)) {
      cout << priority << " value: " << value << endl;
    }
    cout << priority << " value: " << value << endl;
}

void testingBeginandNext3 () {
  cout << "testing begin and next functions!\n\n\n";
  priorityqueue<string> pq2;
  string value;
  int priority;

    pq2.enqueue("Dolores", 5);
    pq2.enqueue("Joshua", 4);
    pq2.enqueue("Brenard", 4);
    pq2.enqueue("Ford", 2);
    pq2.enqueue("Lei", 2);
    pq2.enqueue("Wei", 2);
    pq2.enqueue("Arnold", 8);
    pq2.enqueue("Jasmine", 6);
    pq2.enqueue("Carlos", 11);
    pq2.enqueue("Julian", 11);
    pq2.enqueue("Justin", 11);

  
  pq2.begin();
    while (pq2.next(value, priority)) {
      cout << priority << " value: " << value << endl;
    }
    cout << priority << " value: " << value << endl;
}

void testingDequeue () {
  priorityqueue<string> pq;

    pq.enqueue("Dolores", 5);
    pq.enqueue("Joshua", 4);
    pq.enqueue("Brenard", 4);
    pq.enqueue("Ford", 2);
    pq.enqueue("Lei", 2);
    pq.enqueue("Wei", 2);
    pq.enqueue("Arnold", 8);
    pq.enqueue("Jasmine", 6);
    pq.enqueue("Carlos", 11);
    
    
  cout << pq.toString();
  cout << pq.dequeue() << " " << pq.dequeue() << endl;
}

void testingDequeue2 () {
  priorityqueue<string> pq2;
  
    pq2.enqueue("Dolores", 5);
    pq2.enqueue("Joshua", 4);
    pq2.enqueue("Brenard", 4);
    pq2.enqueue("Ford", 2);
    pq2.enqueue("Lei", 2);
    pq2.enqueue("Wei", 2);
    pq2.enqueue("Arnold", 8);
    pq2.enqueue("Jasmine", 6);
    pq2.enqueue("Carlos", 11);
    pq2.enqueue("Julian", 11);
    pq2.enqueue("Justin", 11);
  int sizeOfPQ = pq2.Size();
  cout << pq2.toString();
  
  //for (int i = 0; i < sizeOfPQ; i++) {
  /*cout << pq2.dequeue() << " ";
  cout << pq2.dequeue() << " ";
  cout << pq2.dequeue() << " ";
  cout << pq2.dequeue() << " ";
  cout << pq2.dequeue() << " ";
  cout << pq2.dequeue() << " ";
  cout << pq2.dequeue() << " ";
  cout << pq2.dequeue() << " ";
  cout << pq2.dequeue() << " ";
  cout << pq2.dequeue() << " ";
  cout << pq2.dequeue() << " ";

  cout << pq2.dequeue() << " ";*/

  for (int i = 0; i < sizeOfPQ; i++) {
    cout << pq2.dequeue() << " ";
  }
  
  
  //}
}

void testingPeek() {
  priorityqueue<string> pq;

    pq.enqueue("Dolores", 5);
    pq.enqueue("Joshua", 4);
    pq.enqueue("Brenard", 4);
    pq.enqueue("Ford", 2);
    pq.enqueue("Lei", 2);
    pq.enqueue("Wei", 2);
    pq.enqueue("Arnold", 8);
    pq.enqueue("Jasmine", 6);
    pq.enqueue("Carlos", 11);

  cout << "Testing peek function:\nExpected: Ford\nRecieved: " << pq.peek();
  pq.clear();
}

void testingPeek2() {
  priorityqueue<string> pq;

    pq.enqueue("Dolores", 5);
    pq.enqueue("Joshua", 5);
    pq.enqueue("Brenard", 4);
    pq.enqueue("Ford", 2);
    pq.enqueue("Arnold", 8);
    pq.enqueue("Jasmine", 6);
    pq.enqueue("Carlos", 11);

  cout << "Testing peek function:\nExpected: Ford\nRecieved: " << pq.peek();
  pq.clear();
}

void testingEquivalence () {
  priorityqueue<string> pq;

    pq.enqueue("Dolores", 5);
    pq.enqueue("Joshua", 5);
    pq.enqueue("Brenard", 4);
    pq.enqueue("Ford", 2);
    pq.enqueue("Arnold", 8);
    pq.enqueue("Jasmine", 6);
    pq.enqueue("Carlos", 11);

  priorityqueue<string> pq2;

    pq2.enqueue("Dolores", 5);
    pq2.enqueue("Joshua", 4);
    pq2.enqueue("Brenard", 4);
    pq2.enqueue("Ford", 2);
    pq2.enqueue("Lei", 2);
    pq2.enqueue("Wei", 2);
    pq2.enqueue("Arnold", 8);
    pq2.enqueue("Jasmine", 6);
    pq2.enqueue("Carlos", 11);

  cout << "Testing equivalence function:\nExpected: Not equal\nRecieved: ";
  if (pq == pq2) {
    cout << "Equal\n";
  } else {
    cout << "Not equal\n";
  }
}

void testingEquivalence2 () {
  priorityqueue<string> pq;

    pq.enqueue("Dolores", 5);
    pq.enqueue("Joshua", 5);
    pq.enqueue("Brenard", 4);
    pq.enqueue("Ford", 2);
    pq.enqueue("Arnold", 8);
    pq.enqueue("Jasmine", 6);
    pq.enqueue("Carlos", 11);

  priorityqueue<string> pq2;

    pq2.enqueue("Dolores", 5);
    pq2.enqueue("Joshua", 5);
    pq2.enqueue("Brenard", 4);
    pq2.enqueue("Ford", 2);
    pq2.enqueue("Arnold", 8);
    pq2.enqueue("Jasmine", 6);
    pq2.enqueue("Carlos", 11);

  cout << "Testing equivalence function:\nExpected: Equal\nRecieved: ";
  if (pq == pq2) {
    cout << "Equal\n";
  } else {
    cout << "Not equal\n";
  }
}


int main () {
  testingEnqueue1();
  testingEnqueue2();
  testingToString();
  testingEqualOperator();
  testingBeginandNext();
  testingBeginandNext2();
  testingBeginandNext3();
  testingPeek();
  testingPeek2();
  testingEquivalence();
  testingEquivalence2();
  testingDequeue();
  testingDequeue2();
}

// TO DO: write lots of tests here.
