(defun multiply-by-seven (number)
  "Multiply Number by seven."
  (interactive "p")
  (message "the result is %d" (* 7 number)))
(multiply-by-seven 2) 


(defun show-buffer-name(buf)
  "show-buffer-name"
  (interactive "B")
  (message "%s" buf))
(show-buffer-name)
