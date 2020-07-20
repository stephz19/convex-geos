(import (chicken io))
(import (chicken bitwise))
(import srfi-1)

(define (read-word)
  ;; eat leading whitespace characters
  (read-token char-whitespace?)
  ;; then read word
  (read-token (complement char-whitespace?)))


(define (read-lines* reader port)
  (let loop [(line-num 1)
             (line (read-line port))]
    (unless (equal? line #!eof)
      ;; send to READER
      (reader line-num line)
      ;; and continue
      (loop (add1 line-num) (read-line port)))))

(define (bit-count n)
  (let loop [(count 0)
             (feed n)]
    (if (zero? feed)
        ;; return our cout
        count
        ;; otherwise continue
        (loop (+ count (bitwise-and feed 1))
              (arithmetic-shift feed -1)))))

(define (bit-indices n)
  (let loop [(val 0)
             (feed n)]
    (if (zero? feed)
        ;; nothing
        '()
        (let [(next (loop (add1 val)
                          (arithmetic-shift feed -1)))]
          (if (zero? (bitwise-and feed 1))
              ;; add nothing
              next
              ;; add this val
              (cons val next)))
        )))

(define (count-sized-sets n size)
  (length (filter
           ;; use this predicate
           (lambda (set) (= (bit-count set) size))
           ;; on the bits
           (bit-indices n))))

(define (bottom-square? n)
  (and (= 2 (count-sized-sets n 1))
       (= 1 (count-sized-sets n 2))))

(define (top-square? n)
  (and (= 2 (count-sized-sets n 4))
       (= 1 (count-sized-sets n 3))))

(define (xor a b)
  (not (equal? a b)))

(define (squarical? id)
  (or (top-square? id)
       (bottom-square? id)))

(define (parse-line line-num)
  ;; line should be of the format: id: <id>
  ;; consume "id: "
  (read-word)

  (let [(id (string->number (read-word)))]
    (when (squarical? id)
      (print line-num ". " id))
    ))

(define (parse-file port)
  ;; iterate through file
  (read-lines* (lambda (line-num line)
                 ;; open string port and bind
                 (parameterize [(current-input-port (open-input-string line))]
                   ;; and parse
                   (parse-line line-num)))
               port))

;; parse file
(call-with-input-file "size-5-ids.txt" parse-file)
