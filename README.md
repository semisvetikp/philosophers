# philosophers


![image](https://user-images.githubusercontent.com/78923396/121812169-8a614a00-cc6f-11eb-98b5-f3d944ebe8d9.png)

Данная работа посвящена решению задач с параллельными процессами на примере задачи об обедающих философах,
предложенной Э.Дейкстрой

N-ое количество философов сидят вокруг круглого стола, перед каждым философом стоит тарелка спагетти. 

Каждый философ может либо есть, либо размышлять, либо спать. Приём пищи не ограничен количеством оставшихся спагетти — подразумевается бесконечный запас. Тем не менее, философ может есть только тогда, когда держит две вилки — взятую справа и слева.

Каждый философ может взять ближайшую вилку (если она доступна) или положить — если он уже держит её. Взятие каждой вилки и возвращение её на стол являются раздельными действиями, которые должны выполняться одно за другим.

Вопрос задачи заключается в том, чтобы разработать модель поведения (параллельный алгоритм), при котором ни один из философов не будет голодать, то есть будет вечно чередовать приём пищи, сон и размышления.

В проекте рассматриваются три варианта условия задачи и их решение: 

1.

  • One fork between each philosopher, therefore if they are multiple philosophers, there will be a fork at the right and the left of each philosopher.
  
  • To avoid philosophers duplicating forks, you should protect the forks state with a mutex for each of them.
  
  • Each philosopher should be a thread.
  
2.

  • All the forks are in the middle of the table.
  
  • They have no states in memory but the number of available forks is represented by a semaphore.
  
  • Each philosopher should be a thread.


3.

  • All the forks are in the middle of the table.
  
  • They have no states in memory but the number of available forks is represented by a semaphore.
  
  • Each philosopher should be a process and the main process should not be a philosopher.
