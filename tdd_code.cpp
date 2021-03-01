//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     PATRIK SKALOS <xskalo01@stud.fit.vutbr.cz>
// $Date:       $2021-02-25
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author PATRIK SKALOS
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
  m_pHead = nullptr;
}

PriorityQueue::~PriorityQueue()
{
  if(m_pHead) {
    while (m_pHead->pNext != nullptr) {
      Element_t *tmp = m_pHead->pNext->pNext;
      delete (m_pHead->pNext);
      m_pHead->pNext = tmp;
    }
    delete (m_pHead);
    m_pHead = nullptr;
  }
}

void PriorityQueue::Insert(int value)
{
  //Vlozenie prveho prvku
  if(!m_pHead){
    m_pHead = new Element_t{
      .pNext = nullptr,
      .value = value
    };
    return;
  }
  //Vlozenie na zaciatok
  if(m_pHead->value <= value){
    Element_t *tmp = m_pHead;
    m_pHead = new Element_t{
      .pNext = tmp,
      .value = value
    };
    return;
  }
  Element_t *prev = m_pHead;
  Element_t *tmp = m_pHead;
  while (tmp->value >= value) {
    //Vlozenie na koniec
    if(tmp->pNext == nullptr){
      tmp->pNext = new Element_t{
        .pNext = nullptr,
        .value = value
      };
      return;
    }
    prev = tmp;
    tmp = tmp->pNext;
  }
  //Vlozenie do stredu
  prev->pNext = new Element_t{
    .pNext = tmp,
    .value = value
  };
}

bool PriorityQueue::Remove(int value)
{
  if(!m_pHead)
    return false;
  Element_t *prev = m_pHead;
  Element_t *tmp = prev->pNext;
  if(m_pHead->value == value) {
    tmp = m_pHead->pNext;
    delete(m_pHead);
    m_pHead = tmp;
    return true;
  }
  while(tmp->value != value) {
    if(tmp->pNext == nullptr)
      return false;
    prev = tmp;
    tmp = tmp->pNext;
  }
  prev->pNext = tmp->pNext;
  delete(tmp);
  return true;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
  if(m_pHead) {
    Element_t *tmp = m_pHead;
    if (tmp->value == value)
      return tmp;
    while (tmp->pNext != nullptr) {
      tmp = tmp->pNext;
      if (tmp->value == value)
        return tmp;
    }
  }
  return nullptr;
}

size_t PriorityQueue::Length()
{
  Element_t *tmp = m_pHead;
  int i = 0;
  for (; tmp; i++)
    tmp = tmp->pNext;
  return i;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
  return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
