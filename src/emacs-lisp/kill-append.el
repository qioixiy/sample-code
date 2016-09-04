(defun my-kill-append (string before-p)
  (setcar kill-ring 
		  (if before-p
			  (concat string (car kill-ring))
			(concat (car kill-ring) string))))

(my-kill-append "test" `t)
(setq kill-ring nil)
kill-ring-max

(defun kill-ring-3()
  (if (car (nthcdr 2 kill-ring))
	  (car (nthcdr 2 kill-ring))
	`(empty)))
(kill-ring-3)
kill-ring
