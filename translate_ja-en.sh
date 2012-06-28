OUTDIR=/data/corpus/translated-wiki/ja-en
mkdir -p $OUTDIR
./corpus_translator -lp:ja:en -limit:400 -database -o:$OUTDIR /data/corpus/wikipedia/xml/ja/pages/
