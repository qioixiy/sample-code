(defun copy-to-buffer (buffer start end)
  "copy to specified buffer the text of the region.
It is inserted into that buffer before its point.
when calling from a program, give three arguments:
a buffer or the name of one, and two character numner s
specifuing the portion of the current buffer to be copied."
  (interactive "BCopy to buffer: \nr")
  (let ((oldbuf (current-buffer)))
	(save-excursion
	  (set-buffer (get-buffer-create buffer))
	  (erase-buffer)
	  (save-excursion
		(insert-buffer-substring oldbuf start end)))))
(copy-to-buffer `test)
(beginning-of-buffer)
