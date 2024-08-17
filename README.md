# Philosophers

This project is an implementation of a solution for the classical multi-threading problem which is the dining philosophers.

## Description

The main idea here is we have N philosophers sitting at a round table and they each have one fork.
Philosophers can do one of three things: eat, think and sleep.
In order to eat, a philosopher needs two forks, after eating a philosopher thinks and then proceeds to sleep.
Depending on the configuration, a philosopher can only go about a certain amount of time without eating.

## Implementation

This C implementation aims to tackle this classical resource sharing problem without causing deadlocks whilst still serving a maximum amount of clients, such a feat is accomplished using the following ideas:
- Mutex locks and condition variables: this will allow us to avoid any potential deadlocks, protecting the shared variables and ensuring their integrity and validity.
- Implementation of a centralized priority queue: this is a necessary step to ensure that no philosophers die, ie the program will use this logic in order to serve resources in an efficient manner

## Usage

- Clone the repository:
	```
		git clone https://github.com/ibenhoci/Philosophers
	```
- Build the project:
	```
		make
	```
- Run the project:
	```
		./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_meals(optionnal)]
	```
	time_to_die: This argument is the time a philosopher has to live, it is refreshed after each meal, it is in ms.
	time_to_eat: This argument is the time a philosopher will spend while eating in ms.
	time_to_sleep: This argument is the time a philosopher will spend sleeping in ms.
	number_of_meals(optional): This argument refers to the number of meals a philosopher will have to eat before the simulation ends.