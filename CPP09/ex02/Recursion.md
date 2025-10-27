void fordJohnsonSort(vector<int>& vec) {
    // Base cases
    if (vec.size() <= 1) return;
    if (vec.size() == 2) { /* swap if needed */ return; }
    
    // 1. Створити пари
    createPairs(vec, larger, smaller, unpaired, has_unpaired);
    
    // 2. ТІЛЬКИ рекурсивний виклик для сортування більших елементів
    fordJohnsonSort(larger);  // ← ТІЛЬКИ ЦЕ рекурсивно
    
    // 3. Решта кроків виконується ТІЛЬКИ НА ПОТОЧНОМУ РІВНІ
    buildMainChain(larger, smaller);
    insertRemainingElements(...);
}

Рівень 1: [21 елемент]
├─ Створити 10 пар + 1 непарний
├─ РЕКУРСІЯ: fordJohnsonSort([10 більших елементів])
│   │
│   Рівень 2: [10 елементів] 
│   ├─ Створити 5 пар
│   ├─ РЕКУРСІЯ: fordJohnsonSort([5 більших елементів])
│   │   │
│   │   Рівень 3: [5 елементів]
│   │   ├─ Створити 2 пари + 1 непарний  
│   │   ├─ РЕКУРСІЯ: fordJohnsonSort([2 більших елементи])
│   │   │   │
│   │   │   Рівень 4: [2 елементи] → Base case: swap
│   │   │   
│   │   ├─ buildMainChain() для рівня 3
│   │   └─ insertRemainingElements() для рівня 3
│   │
│   ├─ buildMainChain() для рівня 2  
│   └─ insertRemainingElements() для рівня 2
│
├─ buildMainChain() для рівня 1
└─ insertRemainingElements() для рівня 1