# Common Mistakes

## General
* Forget to add `;` in the end
* Forget to `return` results or return wrong types

## Binary search
* Forget `-1` in initialize the right index. It should be `right = array.length - 1` for zero-based indexing 
* Forget to update `middle = left + (right - left)/2`
* Accidently use generic array name `a[middle]` instead of the actual one in the problem `letters[middle]` 