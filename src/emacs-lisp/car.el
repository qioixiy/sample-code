;;return the first
(car `(rose violet daisy buffercup))

(car `((lion tiger cheetah)
	   (gazelle antelope zebra)
	   (whale dolphin seal)))

(car (nthcdr 1 `((lion tiger cheetah)
	   (gazelle antelope zebra)
	   (whale dolphin seal))))


