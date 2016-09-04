(let ((zebra `stripes)
	  (tiger `fierce))
  (message "one kind of animal has %s and another is %s."
		   zebra tiger))

(let ((birch 3)
	  pine
	  fir
	  (oak `some))
  (message
   "here are %d variables with %s, %s, and %s value."
   birch pine fir oak))


(defun test-let()
  "let test."
  (interactive)
  (let ((birch 3)
		pine
		fir
		(oak `some))
	(message
	 "here are %d variables with %s, %s, and %s value."
	 birch pine fir oak))
  )
(test-let)

