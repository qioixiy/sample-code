(save-excursion 
  (message "start")
  (point)
  (message "end")
  (goto-line 1))
(goto-line 1)

(message "we are %d characters into this buffer"
		 (- (point)
			(save-excursion
			  (goto-char (point-min)) (point))))
