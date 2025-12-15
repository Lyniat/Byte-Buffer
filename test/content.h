#pragma once
#include <string>

const std::string test_string_european =
    R"(One morning, when Gregor Samsa woke from troubled dreams, he found himself transformed in his bed into a horrible vermin.
He lay on his armour-like back, and if he lifted his head a little he could see his brown belly, slightly domed and divided by arches into stiff sections.
The bedding was hardly able to cover it and seemed ready to slide off any moment.
His many legs, pitifully thin compared with the size of the rest of him, waved about helplessly as he looked.
"What's happened to me?" he thought. It wasn't a dream.
His room, a proper human room although a little too small, lay peacefully between its four familiar walls.
A collection of textile samples lay spread out on the table - Samsa was a travelling salesman - and above it there hung a picture that he had recently cut out of an illustrated magazine and housed in a nice, gilded frame.
It showed a lady fitted out with a fur hat and fur boa who sat upright, raising a heavy fur muff that covered the whole of her lower arm towards the viewer.
Gregor then turned to look out the window at the dull weather. Drops)";

const std::string test_string_haiku =
    R"(古池や
蛙飛び込む
水の音)";

constexpr uint8_t a = 123;
constexpr int8_t b = -4;
constexpr uint16_t c = 7654;
constexpr int16_t d = -6543;
constexpr bool e = false;
constexpr bool f = true;
constexpr float g = 3.14f;
constexpr double h = 1.2345;
constexpr uint32_t i = 2147483647;
constexpr int32_t j = -1073741824;
constexpr uint64_t k = 6158914691266517205;
constexpr int64_t l = -8223272036754775707;

uint8_t _a;
int8_t _b;
uint16_t _c;
int16_t _d;
bool _e;
bool _f;
float _g;
double _h;
uint32_t _i;
int32_t _j;
uint64_t _k;
int64_t _l;