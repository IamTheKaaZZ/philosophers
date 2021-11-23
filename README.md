# Philosophers

✅ Final grade: 125/100
## I’ve never thought philosophy would be so deadly.

_Summary: In this project, you will learn the basics of threading a process. You will
learn how to make threads. You will discover the mutex._

> [Mandatory](philo/README.md)

> [Bonus](philo_bonus/README.md)

# Common Instructions

- Your project must be written in C.
- Your project must be written in accordance with the Norm. If you have bonus
    files/functions, they are included in the norm check and you will receive a 0 if there
    is a norm error inside.
- Your functions should not quit unexpectedly (segmentation fault, bus error, double
    free, etc) apart from undefined behaviors. If this happens, your project will be
    considered non functional and will receive a 0 during the evaluation.
- All heap allocated memory space must be properly freed when necessary. No leaks
    will be tolerated.
- If the subject requires it, you must submit a Makefile which will compile your
    source files to the required output with the flags-Wall,-Wextra and-Werror, use
    cc, and your Makefile must not relink.
- Your Makefile must at least contain the rules $(NAME), all, clean, fclean and
    re.
- To turn in bonuses to your project, you must include a rule bonus to your Makefile,
    which will add all the various headers, libraries or functions that are forbidden on
    the main part of the project. Bonuses must be in a different file_bonus.{c/h}.
    Mandatory and bonus part evaluation is done separately.
- If your project allows you to use your libft, you must copy its sources and its
    associated Makefile in a libft folder with its associated Makefile. Your project’s
    Makefile must compile the library by using its Makefile, then compile the project.
- We encourage you to create test programs for your project even though this work
    **won’t have to be submitted and won’t be graded**. It will give you a chance
    to easily test your work and your peers’ work. You will find those tests especially
    useful during your defence. Indeed, during defence, you are free to use your tests
    and/or the tests of the peer you are evaluating.
- Submit your work to your assigned git repository. Only the work in the git reposi-
    tory will be graded. If Deepthought is assigned to grade your work, it will be done
    after your peer-evaluations. If an error happens in any section of your work during
    Deepthought’s grading, the evaluation will stop.

# Overview

What you should understand to succeed this project:

- One or more philosophers are sitting at a round table either eating, either thinking,
    either sleeping. While they are eating, they do not think or sleep; while thinking
    they don’t eat or sleep; and, of course, while sleeping, they do not eat or think.
- The philosophers sit at a circular table with a large bowl of spaghetti in the center.
- There are some forks on the table. Serving and eating spaghetti with a single fork
    is very inconvenient, so the philosophers will eat with two forks, one for each hand.
- Each time a philosopher finishes eating, they will drop their forks and start sleeping.
    Once they have finished sleeping, they will start thinking. The simulation stops
    when a philosopher dies.
- Every philosopher needs to eat and they should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know when another philosopher is about to die.
- No need to say that philosophers should avoid dying!
