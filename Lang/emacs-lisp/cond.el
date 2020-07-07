(defun triangle-use-cond (number)
  (cond ((<= number 0) 0)
		((= number 1) 1)
		((> number 1)
		 (+ number 
			(triangle-use-cond
			 (1- number))))))
(triangle-use-cond 3)
