me=`cat id`
me2=`echo $me | tr [:lower:] [:upper:]`

tr "$me$me2" "$me2$me"
