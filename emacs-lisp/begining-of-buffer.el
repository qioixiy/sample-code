(defun simplified-beginning-of-buffer (&optional arg)
  "Move point to the beginning of the buffer;
leave mark at previous position."
  (interactive "P")
  (push-mark)
  (goto-char
   ((if arg
		(if (> (buffer-size) 10000)
			(* (prefix-numeric-value arg)
			   (/ (buffer-size) 10))
		  (/ (+ 10 (* (buffer-size)
					  (prefix-numeric-value arg)))
			 10))
	  (point-min)))
   (if arg (forward-line)))
  )
(simplified-beginning-of-buffer)

(defun test-option (&optional argv)
  "test &optional"
  (interactive)
  (if argv
	  (message "have argv")
	(setq argv 56)
	(message "no argv"))
  (message "argv = %d" argv)
  (if (< fill-column argv)
	  `(fill-column is litter than argv)
	`(fill-column is bigger than argv)))

(defun test()
  "test"
  (test-option 12345)
  (test-option 12)
  (test-option))
(test)
