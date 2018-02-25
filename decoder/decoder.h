#ifndef _DECODER_H_
#define _DECODER_H_

#define code(x , y) y=x


/*
 * using in Node (look TreeLib.h)
 * for fast analyze Node
 */
enum encoding
{
    //FUNCTIONS
    code(0xffffff01 , add),
    code(0xffffff02 , sub),
    code(0xffffff03 , mul),
    code(0xffffff04 , div),
    code(0xffffff05 , cos),
    code(0xffffff06 , sin),
    code(0xffffff07 , tg),
    code(0xffffff08 , ctg),
    code(0xffffff09 , sh),
    code(0xffffff0a , ch),
    code(0xffffff0b , th),
    code(0xffffff0c , cth),
    code(0xffffff0d , exp),
    code(0xffffff0e , log),
    code(0xffffff0f , ln),
    code(0xffffff10 , lg),
    code(0xffffff11 , pow),

    // VARIABLE
    code(0xfffffd01 , a),
    code(0xfffffd02 , b),
    code(0xfffffd03 , c),
    code(0xfffffd04 , d),
    code(0xfffffd05 , e),
    code(0xfffffd06 , f),
    code(0xfffffd07 , g),
    code(0xfffffd08 , h),
    code(0xfffffd09 , i),
    code(0xfffffd0a , j),
    code(0xfffffd0b , k),
    code(0xfffffd0c , l),
    code(0xfffffd0d , m),
    code(0xfffffd0e , n),
    code(0xfffffd0f , o),
    code(0xfffffd10 , p),
    code(0xfffffd11 , q),
    code(0xfffffd12 , r),
    code(0xfffffd13 , s),
    code(0xfffffd14 , t),
    code(0xfffffd15 , u),
    code(0xfffffd16 , v),
    code(0xfffffd17 , w),
    code(0xfffffd18 , x),
    code(0xfffffd19 , y),
    code(0xfffffd1a , z),
};


/*
 * using in Node (look TreeLib.h)
 * for fast analyze Node
 */
enum  encoding_type
{
    code(0xfffffff0 , VARIABLE),
    code(0xfffffff1 , FUNCTION),
    code(0xfffffff2 , CONSTANT),
};

/*
 *Decoder functions
 */
encoding_type ToDefCode   (char* symbol);//Don't realized
encoding      ToValueCode (char* symbol);//Don't realized

char* ToStrFromCode (encoding_type define , encoding value);//Don't realized



#endif // DECODER_H_

