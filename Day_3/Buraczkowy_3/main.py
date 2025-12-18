
# ██████╗░██╗░░░██╗██████╗░░█████╗░░█████╗░███████╗██╗░░██╗░█████╗░░██╗░░░░░░░██╗██╗░░░██╗
# ██╔══██╗██║░░░██║██╔══██╗██╔══██╗██╔══██╗╚════██║██║░██╔╝██╔══██╗░██║░░██╗░░██║╚██╗░██╔╝
# ██████╦╝██║░░░██║██████╔╝███████║██║░░╚═╝░░███╔═╝█████═╝░██║░░██║░╚██╗████╗██╔╝░╚████╔╝░
# ██╔══██╗██║░░░██║██╔══██╗██╔══██║██║░░██╗██╔══╝░░██╔═██╗░██║░░██║░░████╔═████║░░░╚██╔╝░░
# ██████╦╝╚██████╔╝██║░░██║██║░░██║╚█████╔╝███████╗██║░╚██╗╚█████╔╝░░╚██╔╝░╚██╔╝░░░░██║░░░
# ╚═════╝░░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚══════╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░╚═╝░░░░░╚═╝░░░



#                             ==(W{==========-      /===-                        
#                               ||  (.--.)         /===-_---~~~~~~~~~------____  
#                               | \_,|**|,__      |===-~___                _,-' `
#                  -==\\        `\ ' `--'   ),    `//~\\   ~~~~`---.___.-~~      
#              ______-==|        /`\_. .__/\ \    | |  \\           _-~`         
#        __--~~~  ,-/-==\\      (   | .  |~~~~|   | |   `\        ,'             
#     _-~       /'    |  \\     )__/==0==-\<>/   / /      \      /               
#   .'        /       |   \\      /~\___/~~\/  /' /        \   /'                
#  /  ____  /         |    \`\.__/-~~   \  |_/'  /          \/'                  
# /-'~    ~~~~~---__  |     ~-/~         ( )   /'        _--~`                   
#                   \_|      /        _) | ;  ),   __--~~                        
#                     '~~--_/      _-~/- |/ \   '-~ \                            
#                    {\__--_/}    / \\_>-|)<__\      \                           
#                    /'   (_/  _-~  | |__>--<__|      |                          
#                   |   _/) )-~     | |__>--<__|      |                          
#                   / /~ ,_/       / /__>---<__/      |                          
#                  o-o _//        /-~_>---<__-~      /                           
#                  (^(~          /~_>---<__-      _-~                            
#                 ,/|           /__>--<__/     _-~                               
#              ,//('(          |__>--<__|     /                  .----_          
#             ( ( '))          |__>--<__|    |                 /' _---_~\        
#          `-)) )) (           |__>--<__|    |               /'  /     ~\`\      
#         ,/,'//( (             \__>--<__\    \            /'  //        ||      
#       ,( ( ((, ))              ~-__>--<_~-_  ~--____---~' _/'/        /'       
#     `~/  )` ) ,/|                 ~-_~>--<_/-__       __-~ _/                  
#   ._-~//( )/ )) `                    ~~-'_/_/ /~~~~~~~__--~                    
#    ;'( ')/ ,)(                              ~~~~~~~~~~                         
#   ' ') '( (/                                                                



def main():
    
    
    szczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczepan=0
# Siajabajka-szonween
# 0:35 ━❍──────── -5:32
# ↻     ⊲  Ⅱ  ⊳     ↺
# VOLUME: ▁▂▃▄▅▆▇ 100%
            
    with open("dane.txt") as f:
        for line in f:
            parts = str(line.strip().split("/n"))
            parts = parts[2:-2]
        
            a = "0"
            b = "0"
#               __
#           _.-'.-'-.__
#        .-'.       '-.'-._ __.--._
# -..'\,-,/..-  _         .'   \   '----._
#  ). /_ _\' ( ' '.         '-  '/'-----._'-.__
#  '.<a} {a>.'     '-r   _      .-.       '-._ \
#  '.\. Y .).'       ( .'  .      .\          '\'.
#  .-')'|'/'-.        \)    )      '',_      _.c_.\
#    .<, ,>.          |   _/\        . ',   :   : \\
#   .' \_/ '.        /  .'   |          '.     .'  \)
#                   / .-'    '-.        : \   _;   ||
#                  / /    _     \_      '.'\ ' /   ||
#                 /.'   .'        \_      .|   \   \|
#                / /   /      __.---'      '._  ;  ||
#               /.'  _:-.____< ,_           '.\ \  ||
#              // .-'     '-.__  '-'-\_      '.\/_ \|
#             ( };====.===-==='        '.    .  \\: \
#              \\ '._        /          :   ,'   )\_ \
#               \\   '------/            \ .    /   )/
#                \|        _|             )Y    |   /
#                 \\      \             .','   /  ,/
#                  \\    _/            /     _/
#                   \\   \           .'    .'
#                    '| '1          /    .'
#                      '. \        |:    /
#                        \ |       /', .'
#                         \(      ( ;z'
#                          \:      \ '(_
#                           \_,     '._ '-.___

            for i in reversed(parts):



                if b=="0":
                    b=i
                elif a=="0":
                    a=i   
                elif i >=a:

                    if a >b:
                        b=a
                    
                    a=i    
               
            print(a,b)
            szczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczepan = szczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczepan + int(a+b)
    print(szczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczszczepan)




# 　　　__　　　　　　　　　　 ／/￣/'￣'￣'￣'i￣'~'ニコニ]＝ヽ
# 　　 （）) )) ￣￣￣￣￣￣)￣￣)￣￣￣)</　　　　　　　i　　ニコニ]＝　|
# 　　　~~~￣￣￣￣￣￣￣￣￣￣<７三三ヽ.＿.＿.＿.＿.i.＿.＿,, -''ニニ"￣￣￣￣i）
# 　　　　　　　　／~/ニニ＝''"~￣ｏ／ーヽ''''~'￣'￣'￣'￣'￣'￣'￣'￣'￣'￣'￣'￣'￣|
# 　　　　　　 　 /＿/＼'￣'￣'￣'￣/＿＿/＼＿i＿＿i＿＿i＿＿i＿＿i＿＿i＿＿i,-''i"
# 　　　　　　　　　　V==7ヽ.＿.＿.＿. V==ヽ~;~√ヽiii√ヽi;√ヽi√ヽi√ヽi√ヽi√ヽフ
main()
