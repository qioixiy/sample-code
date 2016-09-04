(setq animals `(giraffe gazelle lion tiger))

(while animals
  (insert "test")
  (setq animals (cdr animals)))

(setq animals `(giraffe gazelle lion tiger))
(defun print-elements-of-list (list)
  "print each element of list on a line of its own."
  (while list 
	(print (car list))
	(setq list (cdr list))))
(print-elements-of-list animals)


(defun triangle (number-of-rows)
  "get total."
  (let ((total 0)
		(row-number 1))
	(while (<= row-number number-of-rows)
	  (setq total (+ total row-number))
	  (setq row-number (+ 1 row-number)))
	total))
(triangle 2);3
(triangle 3);6
(triangle 4);10

;
(defun digui (number)
  "digui call."
  (if (> number 0)
	(+ number 
	   (digui 
		(- number 1)))
	0))

(digui 2)

