update wiki_corpus set status = 0;
update wiki_corpus set status = 0 where id = 13;

update wiki_corpus set status = 0, result = 0 where id not in (select id from translations)