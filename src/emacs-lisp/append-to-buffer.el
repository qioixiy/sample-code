(defun append-to-buffer (buffer start end)
  "append to specified buffer the text of the region.
It is inserted into that buffer before its point.
when calling from a program, give three arguments:
a buffer or the name of one, and two character numner s
specifuing the portion of the current buffer to be copied."
  (interactive "BAppend to buffer: \nr")
  (let ((oldbuf (current-buffer)))
	(save-excursion
	  (set-buffer (get-buffer-create buffer))
	  (insert-buffer-substring oldbuf start end))))
(append-to-buffer `test) 
(find-tag)
