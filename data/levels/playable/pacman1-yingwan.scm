;; generated by xml2sexpr.rb convert script from 'pacman1-yingwan.pingus'
(pingus-level 
  (version 2)
  (head 
    (levelname )
    (description )
    (author "Ying-Wan Lam <yingwan.lam@yale.edu>")
    (number-of-pingus 50)
    (number-to-save 40)
    (time 9000)
    (actions 
      (basher 12)
      (blocker 10)
      (bomber 10)
      (bridger 12)
      (digger 5)
      (floater 10)
      (jumper 5)
      (miner 5))
    (music "none")
    (levelsize 800 600))
  (objects 
    (surface-background 
      (surface 
        (image "textures/stars")
        (modifier "ROT0"))
      (color 0 0 0 0)
      (scroll-x 0)
      (scroll-y 0)
      (para-x 0)
      (para-y 0)
      (stretch-x 0)
      (stretch-y 0))
    (hotspot 
      (surface 
        (image "global/Ywlam/pacbkg")
        (modifier "ROT0"))
      (position 174 16 -5)
      (speed -1)
      (parallax 1))
    (groundpiece 
      (type "ground")
      (surface 
        (image "global/Ywlam/pacmaze")
        (modifier "ROT0"))
      (position 174 16 0))
    (groundpiece 
      (type "solid")
      (surface 
        (image "global/Ywlam/pacframe")
        (modifier "ROT0"))
      (position 174 16 0))
    (entrance 
      (position 227 99 0)
      (type "generic")
      (direction "right")
      (release-rate 30)
      (owner-id 0))
    (exit 
      (owner-id 0)
      (position 413 459 0)
      (surface 
        (image "global/Ywlam/pacman")
        (modifier "ROT0"))
      (owner-id 0))
    (hotspot 
      (surface 
        (image "global/Ywlam/blinky")
        (modifier "ROT0"))
      (position 430 186 80)
      (speed -1)
      (parallax 1))
    (hotspot 
      (surface 
        (image "global/Ywlam/inky")
        (modifier "ROT0"))
      (position 362 426 80)
      (speed -1)
      (parallax 1))
    (hotspot 
      (surface 
        (image "global/Ywlam/pinky")
        (modifier "ROT0"))
      (position 436 380 80)
      (speed -1)
      (parallax 1))
    (hotspot 
      (surface 
        (image "global/Ywlam/clyde")
        (modifier "ROT0"))
      (position 361 233 80)
      (speed -1)
      (parallax 1))
    (spike 
      (position 360 234 100))
    (spike 
      (position 360 426 100))
    (spike 
      (position 436 379 100))
    (spike 
      (position 431 186 100))))
;; EOF ;;
