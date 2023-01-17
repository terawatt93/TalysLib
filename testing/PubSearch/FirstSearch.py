from scholarly import scholarly
from scholarly import ProxyGenerator
import json
#pub содержит поля:
# author_id - идентификаторы авторов (не сильно нужно)
# ENTRYTYPE - тип публикации
# ID - краткое имя
# Abstract - аннотация
# author - массив авторов
# pub_year - год публикации
# title - название
# venue - журнал/издание
# eprint_url - ссылка, где можно найти pdf (не издателя)
# pub_url - ссылка на сайт издателя со статьей
# url_add_sclib - ссылка на гугловский генератор ссылок на публикации


#127.0.0.1:9050
#нужен tor, чтобы не забанили в google
#для этого нужно установить tor: sudo apt install tor
# в /etc/tor/torrc добавить HTTPTunnelPort 9080
pg = ProxyGenerator()
#success = pg.SingleProxy("127.0.0.1:9080","127.0.0.1:9080")
success = pg.FreeProxies()
#success = pg.Tor_External(9050,9051,"scholarly_password")
scholarly.use_proxy(pg)

# if success :
	# scholarly.use_proxy(pg)
search_query = scholarly.search_pubs('Gamma-ray production cross sections from neutron interaction with iron')
pub=next(search_query)
#j = json.loads(json.dumps(pub._asdict()))
with open('data.json', 'w') as outfile:
	json.dump(pub, outfile)#сгенерировать json из публикации
print(pub)
#print(scholarly.bibtex(pub))
#scholarly.pprint(pub)
