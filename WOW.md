# Way of Work
## How to commit?

1. Create a well described issue on github.
    - What is the goal of you're change / What is there to fix?
    - How will our code benefit from it?
    - Is this feature required for a milestone? (If yes than add a mielstone to it)

2. If the feature you want to add hasn't been discussed inform the team of your idea and discuss wether it is necessary or even doable without huge refactors of the codebase.

3. Create a branch for you're feature/fix and [link it to the issue](https://docs.github.com/en/issues/tracking-your-work-with-issues/linking-a-pull-request-to-an-issue). **PUSHING ANYTHING DIRECTLY TO MAIN BRANCH (without pull requests) IS HEREBY DISABLED FROM 07.12.2023 UNTILL FURTHER NOTICE**.


4. Work on your feature, commit, etc. KEEP TO THE RULES

5. Push your changes onto youre branch **!! NOT MAIN !!**.

6. Add UT's if needed.

7. Pass UT's

8. Enter review.

9. Resolve all comments on the review(this is mandatory).

10. Resolve all merge conflicts.

11. Merge your branch into main and close the pull request (if possible). **AS OF 07.12.2023 ONLY MERGE BY REBASE IS POSSIBLE**

## Programming rules

### 1.  K.I.S.S. (Keep It Simple, Stupid)

    There are many areas where this rule applies in programming.  Two very important ones are:

    1. Subprogram behavior and length:  Subprograms should do precisely ONE conceptual task and no more. The length of a subprogram should allow it to be easily visually inspected; generally no more that one page in length.  Similarly you should generally not mix input/output and algorithmic logic in the same subprogram; it is alway a goal to separate I/O from logic.

    2. If a problem is can be decomposed into two or more independently solvable problems, then solve them independently and after you have implemented and tested the independent solutions, then combine them into the larger result.  This is sometimes known as "Gall's Law":

### 2) "Rule of Three" (code duplication)

    Code refactoring rule of thumb to decide when a replicated piece of code should be replaced by a new procedure. It states that you are allowed to copy and paste the code once, but that when the same code is replicated three times, it should be extracted into a new procedure.

    Duplication in programming is almost always in indication of poorly designed code or poor coding habits. Duplication is a bad practice because it makes code harder to maintain. When the rule encoded in a replicated piece of code changes, whoever maintains the code will have to change it in all places correctly. This process is error-prone and often leads to problems. If the code exists in only one place, then it can be easily changed there. This rule is can even be applied to small number of lines of code, or even single lines of code. For example, if you want to call a function, and then call it again when it fails, it's OK to have two call sites; however, if you want to try it five times before giving up, there should only be one call site inside a loop rather than 5 independent calls.