<h4 align="center"> Anonymous Voting</h4>


<h2 align="center"> Scope</h2>

Alice, Bob, and Carol decided to use the above approach to implement anonymous voting.
That is, they would like to vote on an issue, they would like to know the final result of the
voting, but they do not want to reveal their individual votes. At the end they will all know the
sum of the votes but not the individual votes.
They decided to proceed as follows:

* 1. Alice creates the polynomial A(x) = a2*x^2 + a1*x + a0 where a0 is her vote (an a0
value equal to 1 means “yes” and equal to zero means “no”). The coefficients a1 and
a2 are known only to Alice.

* 2. Bob creates the polynomial  B(x ) = b2 x^2 + b1*x + b0 where b0 is his vote.
* 3. Carol creates the polynomial C(x) =c2*x^2 + c1*x + c0 where c0 is her vote.
* 4. Alice computes A(1) and gives A(2) to Bob and A(3) to Carol.
* 5. Bob computes B(2) and gives B(1) to Alice and B(3) to Carol.
* 6. Carol computes C(3) and gives C(1) to Alice and C(2) to Bob.
* 7. Alice computes D(1) = A(1) + B(1) + C(1).

<h2 align="center"> Implementation</h2>
  Each voter creates a polynomial with their binary vote as the last coefficient.
  Each voter corresponds to a number. They accept the value of each of the other voters' 
  polynomials for that number and sum them all up. The number and the sum of the polynomials
  are a tuple of values.
  From the tuples each voter has created, the polynomial is regressed and the last coefficient
  is the sum of the votes.
  Due to the nature of the Gauss-Jordan algorithm, it is only effective up to polynomials of 
  a certain degree (15-18), meaning that the program can only handle about 15-18 voters.

  Votes are inputed through the command line:
    ```bash
    e.g : ./anon_voting 1 1 0 1 1 0 
    ```
  returns:
   FOR: 4
   AGAINST: 2

<h2 align="center"> Why is d0 the sum of the votes?</h2>
  Each value of D for value x is the sum of all the other polynomials for that same value x.
  Polynomial D is by definition the sum of the other polynomials by parts.
  Therefore we have:
  D(X) = (a2 + b2 + c2)*x^2 + (a1 + b1 + c1)*x + (a0 + b0 + c0)
  The last coefficient is the sum of all the votes.

